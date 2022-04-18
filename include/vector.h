#pragma once

class Vector2
{
public:
  float x;
  float y;

  Vector2 operator + (float f) const;
  Vector2 operator - (float f) const;
  Vector2& operator += (float f);
  Vector2& operator -= (float f);
  Vector2 operator * (float f);
  Vector2& operator += (const Vector2& other);
  Vector2& operator -= (const Vector2& other);

  bool isZero();
};