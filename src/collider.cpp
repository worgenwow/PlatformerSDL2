#include <SDL2/SDL.h>

#include <collider.h>
#include <vector.h>
#include <gameData.h>
#include <entity.h>

Collider::Collider()
{
  mIgnoredColliders = NULL;
}

Collider::~Collider()
{
  if(mIgnoredColliders != NULL)
  {
    delete mIgnoredColliders;
  }
}

Collider::Collider(SDL_Rect rect)
{
  mRect = rect;
  mIgnoredColliders = NULL;
  mIgnoreAmount = 0;
}

void Collider::updateColliderPos(Vector2 position)
{
  mRect.x = (int) position.x;
  mRect.y = (int) position.y;
}

// add collider to ignore when checking for collision
void Collider::addIgnoredCollider(Collider* collider)
{
  if(mIgnoredColliders == NULL)
  {
    mIgnoredColliders = new Collider*[1]{collider};
    mIgnoreAmount = 1;
  }
  else
  {
    Collider** newArray = new Collider*[mIgnoreAmount+1];
    memcpy(newArray, mIgnoredColliders, sizeof(Collider*)*mIgnoreAmount);
    delete mIgnoredColliders;

    mIgnoredColliders = newArray;
    mIgnoredColliders[mIgnoreAmount] = collider; // because arrays start at 0
    mIgnoreAmount++;
  }
}

bool Collider::checkCollision(Collider* collider)
{
  SDL_Rect* otherRect = collider->getRect();
  bool colliding = false;

  // checks if it's colliding in x-axis through AABB
  colliding = mRect.x + mRect.w >= otherRect->x && otherRect->x + otherRect->w >= mRect.x;
  if(!colliding)
  {
    return colliding;
  }

  // AABB on y-axis
  colliding = mRect.y + mRect.h >= otherRect->y && otherRect->y + otherRect->h >= mRect.y;
  return colliding;
}

bool Collider::isIgnored(Collider* collider)
{
  for (int i = 0; i < mIgnoreAmount; i++)
  {
    if(collider == mIgnoredColliders[i])
    {
      return true;
    }
  }
  return false;
}

Collider* Collider::checkAllCollisions(GameData& gameData)
{
  Collider* currentCollider;
  for (int i = 0; i < gameData.entityAmount; i++)
  {
    currentCollider = gameData.entities[i]->getCollider();
    if(currentCollider == this || currentCollider == NULL || isIgnored(currentCollider))
    {
      continue;
    }
    
    if(checkCollision(currentCollider))
    {
      break;
    }
    else
    {
      currentCollider = NULL;
    }
  }
  
  return currentCollider;
}

SDL_Rect* Collider::getRect()
{
  return &mRect;
  // @TODO change?
}