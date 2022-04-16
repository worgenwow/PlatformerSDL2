#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vector.h>
#include <collider.h>
#include <entity.h>
#include <sprite.h>

Entity::Entity(Vector2 position)
{
  mPosition = position;
}

Entity::~Entity()
{

}

bool Entity::loadSprite(SDL_Renderer* renderer, const char* path, SDL_Color& colorKey)
{
  return mSprite.loadFromFile(renderer, path, colorKey);
}

void Entity::addCollider(Collider& collider)
{
  mCollider = collider;
}

Vector2 Entity::getPosition()
{
  return mPosition;
}

Sprite* Entity::getSprite()
{
  return &mSprite;
}