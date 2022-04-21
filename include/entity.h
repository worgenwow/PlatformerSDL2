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
    Sprite* mSprite;
    

    void freeColliders();
    void freeSprite();
    void updateColliderPos();
    void updateVelocity(GameData& gameData, float timeStep);
    void updatePos(GameData& gameData, float timeStep);
    
  protected:
    Vector2 mVelocity; 
    Collider* mCollider;
    Collider* mFloorCheck;
    int mMass = 1;
    bool mGravityEnabled;
    bool mTouchingFloor;
    bool mIsStatic;
    
    virtual Vector2 getForce(GameData& gameData, float timeStep);

  public:
    Entity();
    Entity(Vector2 position, bool gravityEnabled, bool isStatic);
    ~Entity();
    bool loadSprite(SDL_Renderer* renderer, const char* path, SDL_Color& colorKey);
    void addCollider(int width, int height);
    void colliderFromSprite();
    void update(GameData& gameData, float timeStep);
    Vector2 getPosition();
    Sprite* getSprite();
    Collider* getCollider();
};