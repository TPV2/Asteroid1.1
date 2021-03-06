#pragma once

#include <vector>

#include "CollisionSystem.h"
#include "GameCtrlSystem.h"
#include "Manager.h"
#include "RenderSystem.h"
#include "SDLGame.h"
#include "AsteroidsSystem.h"
#include "FighterSystem.h"
#include "BulletSystem.h"
#include "FighterGun.h"

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

	//void addStars(std::size_t n);

	SDLGame *game_;
	Manager *mngr_;
	bool exit_;

	RenderSystem *renderSystem_;
	CollisionSystem *collisionSystem_;
	GameCtrlSystem *gameCtrlSystem_;
	AsteroidsSystem* asteroidsSystem_;
	FighterSystem* fighterSystem_;
	BulletSystem* bulletSystem_;
	FighterGun* fighterGunSystem_;


	const static int _WINDOW_WIDTH_ = 1200;
	const static int _WINDOW_HEIGHT_ = 600;

};
