#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#include <window.h>
#include <timer.h>
#include <collider.h>
#include <entity.h>
#include <gameData.h>
#include <keyData.h>
#include <player.h>
// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Returns false on error
bool init(Window& window)
{
	if(SDL_Init(SDL_INIT_VIDEO)<0)
	{ 
		printf("Failed to initialise SDL2. SDL Error: %s\n", SDL_GetError());
		return false;
	}

	//Set texture filtering to linear
	if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		printf("Warning: Linear texture filtering not enabled.");
	}

	if(!window.create("Platformer", SCREEN_WIDTH, SCREEN_HEIGHT))
	{
		printf("Window creation failed.\n");
		return false;
	}

	int imgFlags = IMG_INIT_PNG;
	if(!(IMG_Init(imgFlags) & imgFlags))
	{
		printf( "Failed to initialise SDL_image. SDL_image Error: %s\n", IMG_GetError() );
		return false;
	}
	return true;
}

// handles keydown and keyup events
void keyEvents(SDL_Keycode keyCode, KeyData& keyData, bool keyDown)
{
	switch(keyCode)
	{
		case SDLK_d:
			keyData.dKeyDown = keyDown;
			break;
		case SDLK_w:
			keyData.wKeyDown = keyDown;
			break;
		case SDLK_a:
			keyData.aKeyDown = keyDown;
			break;
		case SDLK_s:
			keyData.sKeyDown = keyDown;
			break;
	}
}

void handleEvents(SDL_Event& e, bool& exit, KeyData& keyData)
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
	float timeStep = 0;
	timeStep = gameData.stepTimer.getTicks()/1000.f;

	gameData.player.updateVelocity(keyData);
	gameData.player.updatePos(gameData, timeStep);

	gameData.stepTimer.Start();
}

// handle all the rendering in the game
void handleRendering(GameData& gameData, Collider& floor)
{
	SDL_Color white = {0xFF, 0xFF, 0xFF, 0xFF};
	SDL_Rect floorRect = *floor.getRect();

	gameData.window.clearRender();
	gameData.window.renderEntity(gameData.player);
	gameData.window.renderRect(floorRect, white, true);
	gameData.window.updateRender();
}

void gameLoop(Window& window)
{
	bool exit = false;
	SDL_Event e;
	KeyData keyData;

	Timer stepTimer;
	Player player({0,0}, true);
	SDL_Color white = {0xFF, 0xFF, 0xFF, 0xFF};
	player.loadSprite(window.getRenderer(), "Assets/player2.png", white); // 9x27
	Collider collider({0,0,32,32});
	player.addCollider(collider);

	Collider floor({0,SCREEN_HEIGHT-100,SCREEN_WIDTH,100});

	GameData gameData
	{
		window,
		stepTimer,
		player,
		{player.getCollider(), &floor},
	};

	while(!exit)
	{
		handleEvents(e, exit, keyData);
		handleMovement(gameData, keyData);
		handleRendering(gameData, floor);
	}
}

int main(int argc, char* args[])
{
	Window window({0x00, 0xFF, 0xFF, 0xFF}); // Constructs a window with white bg color
	if(!init(window))
	{
		printf("Failed to initialise.\n");
		return 1;
	}
	gameLoop(window);

	IMG_Quit();
	SDL_Quit();
	return 0;
}