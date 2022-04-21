#pragma once
#include <SDL2/SDL.h>

#include <vector.h>
#include <gameData.h>

class Collider
{
  private:
    SDL_Rect mRect;
    Collider** mIgnoredColliders;
    int mIgnoreAmount;

    bool checkCollision(Collider* collider);
  public:
    Collider();
    ~Collider();
    Collider(SDL_Rect rect);
    void addIgnoredCollider(Collider* collider);
    void updateColliderPos(Vector2 position);
    bool isIgnored(Collider* collider);
    Collider* checkAllCollisions(GameData& gameData);
    SDL_Rect* getAABB();
};