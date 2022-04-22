#include <entity.h>
#include <platform.h>

Platform::Platform(SDL_Rect rect) : Entity({(float) rect.x, (float) rect.y}, false, true)
{
  addCollider(rect.w, rect.h, 0, 0);
}