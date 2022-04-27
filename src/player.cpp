#include <player.h>
#include <keyData.h>
#include <math.h>

void Player::setJumpImpulse(int initialJumpHeight, int gravity)
{
  /* uses kinetic energy and gravitational potential energy
     to calculate impulse force required */
  mJumpImpulse = mMass*sqrt(2*initialJumpHeight*gravity);
}

// solves a quadratic equation to find continous force needed to reach full jump height
void Player::setJumpForce(int extraHeight, int gravity, float time)
{
  // https://fenomas.com/2016/07/game-jumping-physics/ for explanation
  float v = sqrt(2*gravity*extraHeight);
  float a = pow(time,2);
  float b = 2 * v * time - gravity * a;
  float c = -2 * gravity * extraHeight;
  mJumpForce = fabs(mMass * (-b + sqrt(pow(b,2) - 4*a*c)) / (2*a));
}

Player::Player(Vector2 position, bool gravityEnabled, int gravity) : Entity(position, gravityEnabled, false)
{
  mMovementForce = 1000;
  mMaxSpeed = 100;
  mMinSpeed = 5;
  int jumpHeight = 32;
  int initialJumpHeight = 16;
  mJumpTime = 0.5;
  mCurrentJumpTime = mJumpTime;

  setJumpForce(jumpHeight - initialJumpHeight, gravity, mJumpTime);
  setJumpImpulse(initialJumpHeight, gravity);
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
    {
      force.y -= mJumpImpulse/timeStep;
      mCurrentJumpTime = 0;
    }
    else
    {
      if(mCurrentJumpTime < mJumpTime)
      {
        force.y -= mJumpForce;
        mCurrentJumpTime += timeStep;
      }
    }
  }

  return force;
}