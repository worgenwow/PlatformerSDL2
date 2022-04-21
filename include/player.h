#pragma once

#include <entity.h>
#include <keyData.h>

class Player: public Entity
{
  private:
    int mMovementSpeed = 100;
    float mJumpImpulse;

    Vector2 getForce(GameData& gameData, float timeStep) override;
    void setImpulse(int jumpHeight, int gravity);
  public:
    KeyData keyData;
    Player(Vector2 position, bool gravityEnabled, int gravity);
};