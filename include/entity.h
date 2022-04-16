#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vector.h>
#include <collider.h>
#include <sprite.h>

class Entity
{
  private:
    // position at top left corner of entity
    Vector2 mPosition;
    Collider mCollider;
    Sprite mSprite;
  public:
    Entity(Vector2 position);
    ~Entity();
    bool loadSprite(SDL_Renderer* renderer, const char* path, SDL_Color& colorKey);
    void addCollider(Collider& collider);
    Vector2 getPosition();
    Sprite* getSprite();
};