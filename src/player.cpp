#include <player.h>
#include <keyData.h>

#include <stdio.h>
Player::Player(Vector2 position, bool gravityEnabled) : Entity(position, gravityEnabled)
{

}

Vector2 Player::getForce(GameData& gameData)
{
  Vector2 force = Entity::getForce(gameData);

  if(keyData.dKeyDown)
  {
    force.x += mMovementSpeed;
  }
  else if(keyData.aKeyDown)
  {
    force.x -= mMovementSpeed;
  }

  if(keyData.wKeyDown)
  {
    if(mTouchingFloor && mVelocity.y>=0)
      force.y = -2000;
  }

  return force;
}