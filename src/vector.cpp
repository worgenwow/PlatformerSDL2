#include <vector.h>

Vector2 Vector2::operator + (float f) const
{
    Vector2 result{x+f, y+f};
    return result;
}

Vector2 Vector2::operator - (float f) const
{
    Vector2 result{x-f, y-f};
    return result;
}

Vector2& Vector2::operator += (float f)
{
    x+=f;
    y+=f;
    return *this;
}

Vector2& Vector2::operator -= (float f)
{
    x-=f;
    y-=f;
    return *this;
}

Vector2 Vector2::operator * (float f)
{
    Vector2 result{x*f, y*f};
    return result;
}

Vector2& Vector2::operator += (const Vector2& other)
{
    x+=other.x;
    y+=other.y;
    return *this;
}

Vector2& Vector2::operator -= (const Vector2& other)
{
    x-=other.x;
    y-=other.y;
    return *this;
}

bool Vector2::isZero()
{
    return x==0 && y ==0;
}