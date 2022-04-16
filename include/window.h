#pragma once
#include <SDL2/SDL.h>

#include <entity.h>
class Window
{
    private:
        SDL_Window* mWindow;
        SDL_Renderer* mRenderer;
        int mWidth;
        int mHeight;
        SDL_Color mBackgroundColor;
    public:
        Window();
        Window(SDL_Color backgroundColor);
        ~Window();
        bool create(const char* title, int width, int height);
        void renderRect(SDL_Rect& rect, SDL_Color& color, bool filled);
        void renderEntity(Entity& entity);
        void clearRender();
        void updateRender();
        int getHeight();
        int getWidth();
        SDL_Renderer* getRenderer();
};