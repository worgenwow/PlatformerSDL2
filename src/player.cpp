#include <player.h>
#include <keyData.h>
#include <math.h>

void Player::setImpulse(int jumpHeight, int gravity)
{
  mJumpImpulse = mMass*sqrt(2*jumpHeight*gravity);
}

Player::Player(Vector2 position, bool gravityEnabled, int gravity) : Entity(position, gravityEnabled, false)
{
  mMovementForce = 1000;
  mMaxSpeed = 100;
  mMinSpeed = 5;
  int jumpHeight = 32;

  setImpulse(jumpHeight, gravity);
}

Vector2 Player::getForce(GameData& gameData, float timeStep)
{
  Vector2 force = Entity::getForce(gameData, timeStep);

  if(keyData.dKeyDown)
  {
    force.x += mMovementForce;
    mMoving = true;
  }
  else if(keyData.aKeyDown)
  {
    force.x -= mMovementForce;
    mMoving = true;
  }
  else // if not moving at all slow player down
  {
    mMoving = false;
    if(mVelocity.x>0)
    {
      force.x -= pow(mVelocity.x,2)/2;
    }
    else if(mVelocity.x<0)
    {
      force.x += pow(mVelocity.x,2)/2;
    }
  }

  if(keyData.wKeyDown)
  {
    if(mTouchingFloor && mVelocity.y>=0)
      force.y = -mJumpImpulse/timeStep;
  }

  return force;
}