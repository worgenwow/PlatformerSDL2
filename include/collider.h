#pragma once
#include <SDL2/SDL.h>

class Collider
{
  private:
    SDL_Rect mCollider;
  public:
    Collider();
    Collider(SDL_Rect& collider);
};