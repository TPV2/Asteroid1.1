#pragma once
#include "Component.h"

struct Health :
	public Component
{
private:
	//Constante que representa las vidas iniciales
	const int STARTED_LIVES = 3;
	//Entero que representa las vidas actuales
	int totalLives = STARTED_LIVES;
public:
	//Constructor de health
	Health() : Component(ecs::Health) {};
	//Devuelve la cantidad de vidas que restan
	inline const int getLives() { return totalLives; };
	//Quita una vida
	inline void takeLife() { totalLives--; };
	//Devuelve true si quedan vidas
	inline bool isAlive() { return totalLives <= 0 ? false : true; };
	//Resetea las vidas a un estado inicial
	inline void resetLives() { totalLives = STARTED_LIVES; };
};


