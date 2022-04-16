#include <SDL2/SDL.h>

#include <collider.h>

Collider::Collider(){}

Collider::Collider(SDL_Rect& collider)
{
  mCollider = collider;
}