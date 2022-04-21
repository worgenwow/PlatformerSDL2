#include <player.h>
#include <keyData.h>
#include <math.h>

void Player::setImpulse(int jumpHeight, int gravity)
{
  mJumpImpulse = mMass*sqrt(2*jumpHeight*gravity);
}

Player::Player(Vector2 position, bool gravityEnabled, int gravity) : Entity(position, gravityEnabled, false)
{
  int jumpHeight = 16;
  setImpulse(jumpHeight, gravity);
}

Vector2 Player::getForce(GameData& gameData, float timeStep)
{
  Vector2 force = Entity::getForce(gameData, timeStep);

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
      force.y = -mJumpImpulse/timeStep;
  }

  return force;
}