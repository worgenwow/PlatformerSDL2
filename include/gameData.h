#pragma once
class Window;
class Timer;
class Entity;
class Player;

enum entityNames
{
	PLAYER,
};
const int setEntityAmount = 4;

struct GameData
{
	Window* window;
	Timer* stepTimer;
	Entity* entities[setEntityAmount];
	const int gravity; // postive cause y is down
	const int entityAmount = setEntityAmount;
};