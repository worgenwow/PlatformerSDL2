#pragma once
#include <SDL2/SDL.h>

class Timer
{
    private:
        Uint32 mStartTicks;
        bool mStarted;
    public:
        Timer();
        void Start();
        Uint32 getTicks();
};