#include <SDL2/SDL.h>
#include <stdio.h>

#include <window.h>
#include <timer.h>
// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

struct KeyData
{
bool 
	upKeyDown = false,
	wKeyDown  = false,
	downKeyDown = false,
	sKeyDown = false;
};

struct GameData
{
	Window& window;
	Timer& stepTimer;
};

// Returns false on error
bool init(Window& window)
{
	if(SDL_Init(SDL_INIT_VIDEO)<0)
	{ 
		printf("Failed to initialise SDL2. SDL Error: %s\n", SDL_GetError());
		return false;
	}

	if(!window.create("Platformer", SCREEN_WIDTH, SCREEN_HEIGHT))
	{
		printf("Window creation failed.\n");
		return false;
	}
	return true;
}

// handles keydown and keyup events
void keyEvents(SDL_Keycode keyCode, KeyData& keyData, bool keyDown)
{
	switch(keyCode)
	{
		case SDLK_UP:
			keyData.upKeyDown = keyDown;
			break;
		case SDLK_w:
			keyData.wKeyDown = keyDown;
			break;
		case SDLK_DOWN:
			keyData.downKeyDown = keyDown;
			break;
		case SDLK_s:
			keyData.sKeyDown = keyDown;
			break;
	}
}

void handleEvents(SDL_Event e, bool& exit, KeyData& keyData)
{
	while(SDL_PollEvent(&e)!=0)
	{
		switch(e.type)
		{
			case SDL_QUIT:
				exit = true;
				break;
			case SDL_KEYDOWN:
				keyEvents(e.key.keysym.sym, keyData, true);
				break;
			case SDL_KEYUP:
				keyEvents(e.key.keysym.sym, keyData, false);
				break;
		}
	}
}

// handle all the movement in the game
void handleMovement(GameData& gameData, KeyData& keyData)
{

	gameData.stepTimer.Start();
}

// handle all the rendering in the game
void handleRendering(GameData& gamedata)
{

}

void gameLoop(Window& window)
{
	bool exit = false;
	SDL_Event e;
	KeyData keyData;

	Timer stepTimer;

	GameData gameData
	{
		window,
		stepTimer,
	};

	while(!exit)
	{
		handleEvents(e, exit, keyData);
		handleMovement(gameData, keyData);

		window.clearRender();
		handleRendering(gameData);
		window.updateRender();
	}
}

int main(int argc, char* args[])
{
	Window window({0xFF, 0xFF, 0xFF, 0xFF}); // Constructs a window with white bg color
	if(!init(window))
	{
		printf("Failed to initialise.\n");
		return 0;
	}
	gameLoop(window);

	SDL_Quit();
	return 0;
}