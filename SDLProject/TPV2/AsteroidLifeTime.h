#pragma once
#include "Component.h"
#include <SDL_stdinc.h> // for Uint32
#include "SDLGame.h"	//Para el getTime()

struct AsteroidLifeTime
	:public Component
{
public:
	AsteroidLifeTime() :
		Component(ecs::AsteroidLifeTime),
		creatiomTime_(0),
		lifeTime_(0) 
	{};

	//Geters
	//Devuelve el nivel actual del asteroide
	const inline int getAstLevel() { return level_; };
	//Devuelve el tiempo en que fue creado el asteroide
	const inline Uint32 getCreationTime() { return creatiomTime_; };
	//Devulve el timpo de vida del asteroide
	const inline Uint32 getLifeTime() { return lifeTime_; };

	//Setters
	//Quita un nivel al asteroide
	void removeLevel() { if (level_ > 0) level_--; };
	//Asigna un level a un asteroide
	inline void setLevel(int value) { level_ = value; };
	//Asigna un tiempo de vida a un asteroide
	inline void setLifeTime(Uint32 value) { lifeTime_ = value; };
	//Asgina el tiempo en el que se creo el asteroide
	inline void startTime() { creatiomTime_ = SDLGame::instance()->getTime(); };
private:
	//Nivel actual del asteroide
	int level_ = 0;
	//Tiempo en el que fue creado el asteroide
	Uint32 creatiomTime_;
	//Tiempo de vida del asteroide
	Uint32 lifeTime_;
};

