#pragma once

#include <entity.h>
#include <keyData.h>

class Player: public Entity
{
  private:
    int mMovementForce;
    float mJumpImpulse;
    float mJumpForce;
    float mJumpTime;
    float mCurrentJumpTime;

    Vector2 getForce(GameData& gameData, float timeStep) override;
    void setJumpImpulse(int initialJumpHeight, int gravity);
    void setJumpForce(int extraHeight, int gravity, int time);
  public:
    KeyData keyData;
    Player(Vector2 position, bool gravityEnabled, int gravity);
};