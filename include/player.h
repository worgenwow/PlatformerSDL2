#pragma once

#include <entity.h>
#include <keyData.h>

class Player: public Entity
{
  private:
    int mMovementSpeed = 100;

    Vector2 getForce(GameData& gameData) override;
  public:
    KeyData keyData;
    Player(Vector2 position, bool gravityEnabled);
};