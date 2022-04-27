#pragma once

#include <entity.h>

// entity with simplified constructor
class Platform : public Entity
{
  public:
    Platform(SDL_Rect rect);
};