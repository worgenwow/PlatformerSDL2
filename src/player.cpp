#include <player.h>
#include <keyData.h>

Player::Player(Vector2 position, bool gravityEnabled) : Entity(position, gravityEnabled)
{

}

void Player::updateVelocity(KeyData& KeyData)
{
  if(KeyData.dKeyDown)
  {
    mVelocity.x = mMovementSpeed;
  }
  else if(KeyData.aKeyDown)
  {
    mVelocity.x = -mMovementSpeed;
  }
  else
  {
    mVelocity.x = 0;
  }
}