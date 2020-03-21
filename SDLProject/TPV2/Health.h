#pragma once
#include "Component.h"

struct Health :
	public Component
{
private:
	const int STARTED_LIVES = 3;
	int totalLives = STARTED_LIVES;
public:
	Health() : Component(ecs::Health) {};
	inline const int getLives() { return totalLives; };
	inline void takeLife() { totalLives--; };
	inline bool isAlive() { return totalLives <= 0 ? false : true; };
	inline void resetLives() { totalLives = STARTED_LIVES; };
};


