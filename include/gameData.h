#pragma once
class Window;
class Timer;
class Entity;
class Player;
class Collider;

const int setColliderAmount = 2;

struct GameData
{
	Window& window;
	Timer& stepTimer;
	Player& player;
	Collider* colliders[setColliderAmount]; // @TODO change to entities?
	const int colliderAmount = setColliderAmount;
	const int gravity = 30; // postive cause y is down
};