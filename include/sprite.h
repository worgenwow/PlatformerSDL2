#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Sprite
{
  private:
    SDL_Texture* mTexture;
    int mWidth;
    int mHeight;
  public:
    Sprite();
    ~Sprite();
    void free();
    bool loadFromFile(SDL_Renderer* renderer, const char* path, SDL_Color& colorKey);
    int getWidth();
    int getHeight();
    SDL_Texture* getTexture();
};