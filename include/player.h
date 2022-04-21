#pragma once

#include <entity.h>
#include <keyData.h>

class Player: public Entity
{
  private:
    int mMovementForce;
    float mJumpImpulse;

    Vector2 getForce(GameData& gameData, float timeStep) override;
    void setImpulse(int jumpHeight, int gravity);
  public:
    KeyData keyData;
    Player(Vector2 position, bool gravityEnabled, int gravity);
};