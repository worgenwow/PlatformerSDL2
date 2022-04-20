#include <SDL2/SDL.h>

#include <collider.h>
#include <vector.h>
#include <gameData.h>
#include <entity.h>

Collider::Collider(){}

Collider::~Collider()
{

}

Collider::Collider(SDL_Rect collider)
{
  mCollider = collider;
}

void Collider::updateColliderPos(Vector2 position)
{
  mCollider.x = (int) position.x;
  mCollider.y = (int) position.y;
}

bool Collider::checkCollision(Collider* collider)
{
  SDL_Rect* rect = collider->getRect();
  bool colliding = false;

  if(mCollider.x>rect->x && mCollider.x<rect->x+rect->w)
  {
    colliding = true;
  }
  else if(mCollider.x+mCollider.w>rect->x && mCollider.x+mCollider.w<rect->x+rect->w)
  {
    colliding = true;
  }
  
  if(mCollider.y>rect->y && mCollider.y<rect->y+rect->h){}
  else if(mCollider.y+mCollider.h>rect->y && mCollider.y+mCollider.h<rect->y+rect->h){}
  else
  {
    colliding = false;
  }

  return colliding;
}

Collider* Collider::checkAllCollisions(GameData& gameData)
{
  Collider* currentCollider;
  for (int i = 0; i < gameData.entityAmount; i++)
  {
    currentCollider = gameData.entities[i]->getCollider();
    if(currentCollider == this || currentCollider == NULL)
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
  return &mCollider;
  // @TODO change?
}