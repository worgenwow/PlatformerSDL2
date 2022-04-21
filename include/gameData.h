#pragma once
class Window;
class Timer;
class Entity;
class Player;

enum entityNames
{
	PLAYER,
	FLOOR,
};
const int setEntityAmount = 2;

struct GameData
{
	Window* window;
	Timer* stepTimer;
	Entity* entities[setEntityAmount];
	const int gravity; // postive cause y is down
	const int entityAmount = setEntityAmount;
};