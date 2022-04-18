#pragma once

#include <entity.h>
#include <keyData.h>

class Player: public Entity
{
  private:
    int mMovementSpeed = 100;
  public:
    Player(Vector2 position, bool gravityEnabled);
    void updateVelocity(KeyData& keyData);
};