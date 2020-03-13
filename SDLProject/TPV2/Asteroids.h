#pragma once

#include <vector>

#include "Manager.h"
#include "SDLGame.h"

class Asteroids {

public:
	Asteroids();
	virtual ~Asteroids();

	// from SDLGame
	void start();
	void stop();

private:
	void initGame();
	void closeGame();
	void handleInput();
	void update();
	void render();

#pragma region implementación
	void createEntities();

#pragma endregion

	SDLGame* game_;
	EntityManager* entityManager_;
	bool exit_;

	const static int _WINDOW_WIDTH_ = 800;
	const static int _WINDOW_HEIGHT_ = 600;

};
