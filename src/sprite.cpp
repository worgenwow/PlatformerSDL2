#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#include <sprite.h>

Sprite::Sprite()
{
  mTexture = NULL;
  mWidth = 0;
  mHeight = 0;
}

Sprite::~Sprite()
{
  free();
}

void Sprite::free()
{
  if(mTexture != NULL)
  {
    SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
  }
}

bool Sprite::loadFromFile(SDL_Renderer* renderer, const char* path, SDL_Color& colorKey)
{
  free(); // removes previous texture if any

  SDL_Texture* newTexture = NULL;
  
  SDL_Surface* loadedSurface = IMG_Load(path);
  if(loadedSurface == NULL)
  {
    printf("Unable to load image %s. SDL_image Error: %s\n", path, IMG_GetError());
    return false;
  }

  // SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, colorKey.r, colorKey.g, colorKey.b));
  newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
  if(newTexture == NULL)
  {
    printf("Unable to create texture from %s. SDL Error: %s\n", path, SDL_GetError());
    return false;
  }

  mWidth = loadedSurface->w;
  mHeight = loadedSurface->h;

  SDL_FreeSurface(loadedSurface);
  mTexture = newTexture;
  return mTexture != NULL;
}

int Sprite::getWidth()
{
  return mWidth;
}

int Sprite::getHeight()
{
  return mHeight;
}

SDL_Texture* Sprite::getTexture()
{
  return mTexture;
}