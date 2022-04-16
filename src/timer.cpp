#include <SDL2/SDL.h>

#include <timer.h>

Timer::Timer()
{
    mStarted = false;
}

void Timer::Start()
{
    mStarted = true;
    mStartTicks = SDL_GetTicks();
}

Uint32 Timer::getTicks()
{
    Uint32 time = 0;
    if(mStarted)
    {
        time = SDL_GetTicks() - mStartTicks;
    }
    return time;
}