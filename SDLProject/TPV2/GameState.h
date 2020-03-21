#pragma once
#include "Component.h"

//Enum que representa el estado del juego
enum class STATE
{
	STOPPED = 0,//Antes de empezar el juego
	STARTED,	//Cuando se está jugando
	FINISHED	//Cuando se acaba el juego
};

struct GameState : 
	public Component
{
private:
	STATE currState = STATE::STOPPED;//Inicializado en stopped

public:
	//Constructor
	GameState() :
		Component(ecs::GameState){}

	const STATE getCurrSTate() { return currState; };
	inline void setCurrState(STATE state) { currState = state; };
};

