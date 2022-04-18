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
}

Entity::~Entity()
{

}

bool Entity::loadSprite(SDL_Renderer* renderer, const char* path, SDL_Color& colorKey)
{
  return mSprite.loadFromFile(renderer, path, colorKey);
}

void Entity::addCollider(Collider& collider) // @TODO make sure collider doesn't deallocate on function end
{
  mCollider = collider;

  SDL_Rect* entityCollider = mCollider.getRect();
  SDL_Rect floorCheck;
  floorCheck.x = entityCollider->x;
  floorCheck.w = entityCollider->w;
  floorCheck.y = entityCollider->y + entityCollider->h;
  floorCheck.h = 4;

  mFloorCheck = Collider(floorCheck);
}

void Entity::updatePos(GameData& gameData, float timeStep)
{
  mTouchingFloor = mFloorCheck.checkAllCollisions(gameData) != NULL;
  if(mGravityEnabled && !mTouchingFloor)
  {
    mVelocity.y += gameData.gravity*timeStep;
  }else if(mTouchingFloor && mVelocity.y>0)
  {
    mVelocity.y = 0;
  }

  Vector2 displacement = mVelocity*timeStep;
  if(!displacement.isZero())
  {
    mPosition += displacement;
    updateCollider();

    Collider* hitCollider = mCollider.checkAllCollisions(gameData);
    if(hitCollider != NULL)
    {
      mPosition -= displacement;
      // mPosition.y = hitCollider->getRect()->y-mCollider.getRect()->h;
      updateCollider();
    }
  }
}

Vector2 Entity::getPosition()
{
  return mPosition;
}

Sprite* Entity::getSprite()
{
  return &mSprite;
}

Collider* Entity::getCollider()
{
  return &mCollider;
}

void Entity::updateCollider()
{
  mCollider.updateColliderPos(mPosition);
  mFloorCheck.updateColliderPos({mPosition.x, mPosition.y+32});
}