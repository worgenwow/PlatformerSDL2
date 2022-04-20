#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vector.h>
#include <collider.h>
#include <entity.h>
#include <sprite.h>
#include <gameData.h>

#include <stdio.h>

Entity::Entity(Vector2 position, bool gravityEnabled)
{
  mPosition = position;
  mVelocity = {0,0};
  mGravityEnabled = gravityEnabled;
  mTouchingFloor = false;

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
void Entity::addCollider(int width, int height)
{
  if(mCollider!=NULL)
  {
    freeColliders();
  }

  mCollider = new Collider({0,0,width,height});

  if(mGravityEnabled)
  {
    SDL_Rect floorCheck{0,0,width,1};
    mFloorCheck = new Collider(floorCheck);
  }
  updateColliderPos();
}

void Entity::colliderFromSprite()
{
  int width = mSprite->getWidth();
  int height = mSprite->getHeight();

  addCollider(width, height);
}

Vector2 Entity::getForce(GameData& gameData)
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
  mTouchingFloor = mFloorCheck->checkAllCollisions(gameData) != NULL;

  updateVelocity(gameData, timeStep);
  updatePos(gameData, timeStep);
}

void Entity::updateVelocity(GameData& gameData, float timeStep)
{
  Vector2 velocityChange = (getForce(gameData)/mMass)*timeStep;
  mVelocity += velocityChange;

  if(mTouchingFloor && mVelocity.y > 0)
  {
    mVelocity.y = 0;
  }
}

void Entity::updatePos(GameData& gameData, float timeStep)
{
  Vector2 displacement = mVelocity*timeStep; // velocity * time between frame (in seconds) = displacement
  if(!displacement.isZero())
  {
    mPosition += displacement;
    updateColliderPos();

    Collider* hitCollider = mCollider->checkAllCollisions(gameData);
    if(hitCollider != NULL) //@TODO fix this so that entity will land but can still move
    {
      mPosition -= displacement;
      updateColliderPos();
    }
  }
}

Vector2 Entity::getPosition()
{
  return mPosition;
}

Sprite* Entity::getSprite()
{
  return mSprite;
}

Collider* Entity::getCollider()
{
  return mCollider;
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