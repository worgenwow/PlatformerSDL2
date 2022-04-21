#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#include <window.h>
#include <timer.h>
#include <collider.h>
#include <entity.h>
#include <gameData.h>
#include <player.h>
#include <platform.h>
// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Returns false on error
bool init(Window* window)
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

	if(!window->create("Platformer", SCREEN_WIDTH, SCREEN_HEIGHT))
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
void keyEvents(GameData& gameData, SDL_Keycode keyCode, bool keyDown)
{
	Player* player = static_cast<Player*>(gameData.entities[PLAYER]);

	switch(keyCode)
	{
		case SDLK_d:
			player->keyData.dKeyDown = keyDown;
			break;
		case SDLK_w:
			player->keyData.wKeyDown = keyDown;
			break;
		case SDLK_a:
			player->keyData.aKeyDown = keyDown;
			break;
		case SDLK_s:
			player->keyData.sKeyDown = keyDown;
			break;
	}
}

void handleEvents(SDL_Event& e, bool& exit, GameData& gameData)
{
	while(SDL_PollEvent(&e)!=0)
	{
		switch(e.type)
		{
			case SDL_QUIT:
				exit = true;
				break;
			case SDL_KEYDOWN:
				keyEvents(gameData, e.key.keysym.sym, true);
				break;
			case SDL_KEYUP:
				keyEvents(gameData, e.key.keysym.sym, false);
				break;
		}
	}
}

// handle all the movement in the game
void handleMovement(GameData& gameData)
{
	float timeStep = 0;
	timeStep = gameData.stepTimer->getTicks()/1000.f;

	for (int i = 0; i < gameData.entityAmount; i++)
	{
		gameData.entities[i]->update(gameData, timeStep);
	}
	
	gameData.stepTimer->Start();
}

// handle all the rendering in the game
void handleRendering(GameData& gameData)
{
	SDL_Color white = {0xFF, 0xFF, 0xFF, 0xFF};

	gameData.window->clearRender();
	for (int i = 1; i < gameData.entityAmount; i++)
	{
		gameData.window->renderEntity(gameData.entities[i]);
	}
	gameData.window->renderEntity(gameData.entities[PLAYER]);
	gameData.window->updateRender();
}

void initEntities(GameData& gameData)
{
	SDL_Color white = {0xFF, 0xFF, 0xFF, 0xFF};

	// Player entity
	gameData.entities[PLAYER]->loadSprite(gameData.window->getRenderer(), "Assets/player2.png", white);
	gameData.entities[PLAYER]->colliderFromSprite();
}

void gameLoop(Window* window)
{
	bool exit = false;
	SDL_Event e;
	KeyData keyData;

	const int gravity = 200;
	Timer stepTimer;

	// remember to change setEntityAmount in <gameData.h>
	Player player({SCREEN_WIDTH/2,SCREEN_HEIGHT/2}, true, gravity);
	Platform floor({0,SCREEN_HEIGHT-100,SCREEN_WIDTH,100});

	int width = 20, height = 10;
	Platform platform1({370, 360, width, height});
	Platform platform2({370+width*4, 360-24, width, height});

	GameData gameData
	{
		window,
		&stepTimer,
		{&player, &floor, &platform1, &platform2},
		gravity,
	};

	initEntities(gameData);

	while(!exit)
	{
		handleEvents(e, exit, gameData);
		handleMovement(gameData);
		handleRendering(gameData);
	}
}

int main(int argc, char* args[])
{
	Window window({0x00, 0xFF, 0xFF, 0xFF}); // Constructs a window with white bg color
	if(!init(&window))
	{
		printf("Failed to initialise.\n");
		return 1;
	}
	gameLoop(&window);

	IMG_Quit();
	SDL_Quit();
	return 0;
}