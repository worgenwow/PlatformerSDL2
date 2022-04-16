#include <SDL2/SDL.h>
#include <stdio.h>

#include <window.h>

// Runs when Window is created
Window::Window()
{
    mBackgroundColor = {0xFF, 0xFF, 0xFF, 0xFF}; // Default bg color to white
}

Window::Window(SDL_Color backgroundColor)
{
    mBackgroundColor = backgroundColor;
}

// Runs when Window is destroyed
Window::~Window()
{
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    mWindow = NULL;
    mRenderer = NULL;
}

// Creates the window and renderer, returns success bool
bool Window::create(const char* title, int width, int height)
{
    mWidth = width;
    mHeight = height;

    mWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, mWidth, mHeight, SDL_WINDOW_SHOWN);
    if(mWindow == NULL)
    {
        printf("Failed to create SDL window. SDL Error: %s\n", SDL_GetError());
        return false;
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(mRenderer == NULL)
    {
        printf("Failed to create SDL renderer. SDL Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void Window::renderRect(SDL_Rect rect, SDL_Color color, bool filled)
{
    SDL_SetRenderDrawColor(mRenderer, color.r, color.g, color.b, color.a);
    if(filled)
    {
        SDL_RenderFillRect(mRenderer, &rect);
    }
    else
    {
        SDL_RenderDrawRect(mRenderer, &rect);
    }
}

void Window::clearRender()
{
    SDL_SetRenderDrawColor(mRenderer, mBackgroundColor.r, mBackgroundColor.g, mBackgroundColor.b, mBackgroundColor.a);
    SDL_RenderClear(mRenderer);
}

void Window::updateRender()
{
    SDL_RenderPresent(mRenderer);
}

int Window::getHeight()
{
    return mHeight;
}

int Window::getWidth()
{
    return mWidth;
}