#pragma once
#include <SDL2/SDL.h>

#include <vector.h>
#include <gameData.h>

class Collider
{
  private:
    SDL_Rect mCollider;

    bool checkCollision(Collider* collider);
  public:
    Collider();
    ~Collider();
    Collider(SDL_Rect collider);
    void updateColliderPos(Vector2 position);
    Collider* checkAllCollisions(GameData& gameData);
    SDL_Rect* getRect();
};