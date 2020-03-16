#pragma once
#include "Component.h"
#include <SDL_stdinc.h> // for Uint32

//incluye el número de generaciones del asteroid
struct AsteroidLifeTime
	:public Component
{
	AsteroidLifeTime() :
		Component(ecs::AsteroidLifeTime),
		creatiomTime_(0),
		lifeTime_(0) 
	{};

	int level_ = 0;
	Uint32 creatiomTime_;
	Uint32 lifeTime_;
};

