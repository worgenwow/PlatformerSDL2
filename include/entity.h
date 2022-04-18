#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vector.h>
#include <collider.h>
#include <sprite.h>
#include <gameData.h>

class Entity
{
  private:
    // position at top left corner of entity
    Vector2 mPosition;
    Sprite mSprite;
  protected:
    Vector2 mVelocity; 
    Collider mCollider;
    Collider mFloorCheck;
    bool mGravityEnabled;
    bool mTouchingFloor;
    
    void updateCollider();
  public:
    Entity();
    Entity(Vector2 position, bool gravityEnabled);
    ~Entity();
    bool loadSprite(SDL_Renderer* renderer, const char* path, SDL_Color& colorKey);
    void addCollider(Collider& collider);
    void updatePos(GameData& gameData, float timeStep);
    Vector2 getPosition();
    Sprite* getSprite();
    Collider* getCollider();
};