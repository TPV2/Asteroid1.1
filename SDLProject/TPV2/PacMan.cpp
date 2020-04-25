#include "SDL_macros.h"
#include "PacMan.h"
#include <assert.h>

#include "ImageComponent.h"
#include "InputHandler.h"
#include "Transform.h"
#include "SDLGame.h"

#include "SDL_macros.h"
#include "StarsSystem.h"
#include "StarsPool.h"
#include "AsteroidPool.h"

using namespace std;

PacMan::PacMan() :
		game_(nullptr), //
		mngr_(nullptr), //
		exit_(false) {
	initGame();
}

PacMan::~PacMan() {
	closeGame();
}

void PacMan::initGame() {

	game_ = SDLGame::init("Asteroids", _WINDOW_WIDTH_, _WINDOW_HEIGHT_);
	//StarsPool::init(5);
	AsteroidPool::init();
	BulletPool::init(30);

	mngr_ = new Manager(game_);

	renderSystem_ = mngr_->addSystem<RenderSystem>();
	//starsSystem_ = mngr_->addSystem<StarsSystem>();
	//pacmanSystem_ = mngr_->addSystem<PacManSystem>();
	collisionSystem_ = mngr_->addSystem<CollisionSystem>();
	gameCtrlSystem_ = mngr_->addSystem<GameCtrlSystem>();
	//
	asteroidsSystem_ = mngr_->addSystem<AsteroidsSystem>();
	fighterSystem_ = mngr_->addSystem<FighterSystem>();
	bulletSystem_ = mngr_->addSystem<BulletSystem>();
	fighterGunSystem_ = mngr_->addSystem<FighterGun>();
}

void PacMan::closeGame() {
	delete mngr_;
}

void PacMan::start() {
	exit_ = false;
	auto ih = InputHandler::instance();

	while (!exit_) {
		Uint32 startTime = game_->getTime();
		SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0x00AAAAFF));
		SDL_RenderClear(game_->getRenderer());
		game_->getTextureMngr()->getTexture(Resources::Background)->render({ 0,0,_WINDOW_WIDTH_,_WINDOW_HEIGHT_ });

		ih->update();
		if (ih->keyDownEvent()) {
			if (ih->isKeyDown(SDLK_ESCAPE)) {
				exit_ = true;
				break;
			}
		}

		mngr_->refresh();

		gameCtrlSystem_->update();
		//starsSystem_->update();
		//pacmanSystem_->update();
		collisionSystem_->update();
		renderSystem_->update();
		//
		asteroidsSystem_->update();
		fighterSystem_->update();
		bulletSystem_->update();
		fighterGunSystem_->update();

		SDL_RenderPresent(game_->getRenderer());

		Uint32 frameTime = game_->getTime() - startTime;
		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
}


