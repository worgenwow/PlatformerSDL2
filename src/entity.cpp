#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vector.h>
#include <collider.h>
#include <entity.h>
#include <sprite.h>
#include <gameData.h>
#include <window.h>
#include <math.h>

Entity::Entity(Vector2 position, bool gravityEnabled, bool isStatic)
{
  mPosition = position;
  mVelocity = {0,0};
  mGravityEnabled = gravityEnabled;
  mTouchingFloor = false;
  mIsStatic = isStatic;
  mMoving = false;
  mXOffset = 0;
  mYOffset = 0;

  mSprite = NULL;
  mFloorCheck = NULL;
  mCollider = NULL;
}

Entity::~Entity()
{
  if(mCollider!=NULL)
  {
    freeColliders();
  }
  if(mSprite!=NULL)
  {
    freeSprite();
  }
}

void Entity::freeColliders()
{ 
  delete mCollider;
  mCollider = NULL;

  if(mGravityEnabled)
  {
    delete mFloorCheck;
    mFloorCheck = NULL;
  }
}

void Entity::freeSprite()
{
  delete mSprite;
  mSprite = NULL;
}

bool Entity::loadSprite(SDL_Renderer* renderer, const char* path, SDL_Color& colorKey)
{
  if(mSprite!=NULL)
  {
    freeSprite();
  }

  mSprite =  new Sprite();
  return mSprite->loadFromFile(renderer, path, colorKey);
}

// add or replace collider
void Entity::addCollider(int width, int height, int xOffset, int yOffset)
{
  if(mCollider!=NULL)
  {
    freeColliders();
  }
  
  mXOffset = xOffset;
  mYOffset = yOffset;
  mPosition = {mPosition.x + xOffset, mPosition.y + yOffset};

  mCollider = new Collider({0,0,width,height});
  if(mGravityEnabled)
  {
    SDL_Rect floorCheck{0,0,width,1};
    mFloorCheck = new Collider(floorCheck);

    mFloorCheck->addIgnoredCollider(mCollider);
  }
  updateColliderPos();
}

void Entity::colliderFromSprite()
{
  int width = mSprite->getWidth();
  int height = mSprite->getHeight();

  addCollider(width, height, 0, 0);
}

Vector2 Entity::getForce(GameData& gameData, float timeStep)
{
  Vector2 force = {0,0};
  if(mGravityEnabled)
  {
    force.y += gameData.gravity*mMass;
  }

  return force;
}

void Entity::update(GameData& gameData, float timeStep)
{
  if(mIsStatic){return;}

  if(mGravityEnabled)
  {
    mTouchingFloor = mFloorCheck->checkAllCollisions(gameData) != NULL;
  }
  
  updateVelocity(gameData, timeStep);
  updatePos(gameData, timeStep);
}

void Entity::updateVelocity(GameData& gameData, float timeStep)
{
  Vector2 velocityChange = (getForce(gameData, timeStep)/mMass)*timeStep;
  mVelocity += velocityChange;

  if(abs(mVelocity.x) < mMinSpeed && !mMoving)
  {
    mVelocity.x = 0;
  }
  else if(mVelocity.x > mMaxSpeed)
  {
    mVelocity.x = mMaxSpeed;
  }
  else if(mVelocity.x < -mMaxSpeed)
  {
    mVelocity.x = -mMaxSpeed;
  }

  if(mTouchingFloor && mVelocity.y > 0)
  {
    mVelocity.y = 0;
  }
}

void Entity::updatePos(GameData& gameData, float timeStep)
{
  Vector2 displacement = mVelocity*timeStep; // velocity * time between frame (in seconds) = displacement
  if(displacement.isZero()){return;}

  // gets current position in case we collide
  const int prevX = mCollider->getAABB()->x;
  const int prevY = mCollider->getAABB()->y;

  // moves player
  mPosition += displacement;
  updateColliderPos();

  // checking collisions
  Collider* hitCollider = mCollider->checkAllCollisions(gameData);
  if(hitCollider != NULL)
  {
    resetPos(hitCollider, prevX, prevY);
    updateColliderPos();
  }

  // checks if entity is going off level border
  if(mPosition.x<0)
  {
    mPosition.x = 0;
    mVelocity.x = 0;
  }
  else if(mPosition.x+mCollider->getAABB()->w > gameData.window->getWidth())
  {
    mPosition.x = gameData.window->getWidth() - mCollider->getAABB()->w;
    mVelocity.x = 0;
  }
}

void Entity::resetX(SDL_Rect* hitRect, SDL_Rect* rect, bool right)
{
  mVelocity.x = 0;
  if(right)
  {
    mPosition.x = hitRect->x - rect->w;
  }
  else
  {
    mPosition.x = hitRect->x + hitRect->w;
  }
}

void Entity::resetY(SDL_Rect* hitRect, SDL_Rect* rect, bool down)
{
  mVelocity.y = 0;
  if(down)
  {
    mPosition.y = hitRect->y - rect->h; // place entity on object
  }
  else
  {
    mPosition.y = hitRect->y + hitRect->h; // place entity under object
  }
}

void Entity::resetPos(Collider* hitCollider, const int prevX, const int prevY)
{
  //@TODO improve this
  SDL_Rect* rect = mCollider->getAABB();
  SDL_Rect* hitRect = hitCollider->getAABB();

  int xChange = rect->x - prevX;
  int yChange = rect->y - prevY;
  bool right = xChange > 0;
  bool down = yChange > 0;

  if(xChange == 0 && yChange == 0){return;}
  if(xChange == 0) // thus had to collide on y
  {
    resetY(hitRect, rect, down);
    return;
  }

  if(yChange == 0)
  {
    resetX(hitRect, rect, right);
    return;
  }

  // if it was already colliding on x, means collision must be on y
  if(prevX + rect->w > hitRect->x && hitRect->x + hitRect->w > prevX)
  {
    resetY(hitRect, rect, down);
    return;
  }
  if(prevY + rect->h > hitRect->y && hitRect->y + hitRect->h > prevY)
  {
    resetX(hitRect, rect, right);
    return;
  }

  float slope = (float)yChange/(float)xChange; // working out the line of collision
  int xPos = rect->x; // coordinates of corner
  int yPos = rect->y; // that's closest to hit object
  if(right) // collision originated from right side
  {
    xPos += rect->w;
  }
  if(down)
  {
    yPos += rect->h;
  }
  float yIntersect = yPos - slope*xPos;

  int hitX = hitRect->x;
  int hitY = hitRect->y;
  int hitW = hitRect->w;
  int hitH = hitRect->h;

  // check if line of collision hit side first
  if(right) // check direction so we know what side to check
  {
    // we know x value of closest side, find y value at that point
    float rectIntersect = hitX*slope + yIntersect;
    if(hitY <= rectIntersect && rectIntersect <= hitY + hitH) // see if that y value is within the object
    {
      // if it is within the object it collided with side first
      resetX(hitRect, rect, right);
      return;
    }
  }
  else
  {
    float rectIntersect = (hitX+hitW)*slope + yIntersect;
    if(hitY <= rectIntersect && rectIntersect <= hitY + hitH)
    {
      resetX(hitRect, rect, right);
      return;
    }
  }

  // now checking if it hit top or bottom first
  if(down)
  {
    // similar to whether hit side first, but we work out x value
    float rectIntersect = (hitY-yIntersect)/slope;
    if(hitX <= rectIntersect && rectIntersect <= hitX + hitW)
    {
      resetY(hitRect, rect, down);
      return;
    }
  }
  else
  {
    float rectIntersect = (hitY+hitH-yIntersect)/slope;
    if(hitX <= rectIntersect && rectIntersect <= hitX + hitW)
    {
      resetY(hitRect, rect, down);
      return;
    }
  }
}

Vector2* Entity::getPosition()
{
  return &mPosition;
}

Sprite* Entity::getSprite()
{
  return mSprite;
}

Collider* Entity::getCollider()
{
  return mCollider;
}

int Entity::getXOffset()
{
  return mXOffset;
}

int Entity::getYOffset()
{
  return mYOffset;
}

void Entity::updateColliderPos()
{
  if(mCollider==NULL){return;}
  mCollider->updateColliderPos(mPosition);

  if(mGravityEnabled)
  {
    mFloorCheck->updateColliderPos({mPosition.x, mPosition.y+32});
  }
}