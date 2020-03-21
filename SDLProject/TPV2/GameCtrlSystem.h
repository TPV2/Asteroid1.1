#pragma once

#include "ecs.h"
#include "System.h"
#include "Score.h"
#include "AsteroidsSystem.h"
#include "GameState.h"
#include "Health.h"
#include "AsteroidPool.h"
#include "BulletPool.h"



class GameCtrlSystem: public System {
private:
	const int START_ASTEROIDS = 10;
public:

	//Constructor
	GameCtrlSystem() :
		System(ecs::_sys_GameCtrl) {
	}

	//Agrega los componentes Score y GameState
	void init() override {
		Entity *e = mngr_->addEntity();
		e->addComponent<Score>();
		e->addComponent<GameState>();
		if (e != nullptr) {
			mngr_->setHandler(ecs::_hdlr_GameState, e);
		}
	}

	// - si el juego est� parado y el jugador pulsa ENTER empieza una nueva ronda:
	// 1) a�adir 10 asteroides llamando a addAsteroids del AsteroidsSystem.
	// 2) actualizar el estado del juego y el n�mero de vidas (si es necesario)
	// en los componentes correspondientes (Score, Heath, GameState, �).
	void update() override {
		auto ih = game_->getInputHandler();
		auto gS = GETCMP2(mngr_->getHandler(ecs::_hdlr_GameState), GameState);

		if (gS->getCurrSTate() == STATE::STOPPED && ih->keyDownEvent() && ih->isKeyDown(SDLK_RETURN)) {
			gS->setCurrState(STATE::STARTED);
			mngr_->getSystem<AsteroidsSystem>(ecs::_sys_Asteroids)->addAsteroids(START_ASTEROIDS);
			auto figHealth = GETCMP2(mngr_->getHandler(ecs::_hdlr_Fighter), Health);
		}
	}

	//M�todo que se llama cuando el figher pierde una vida
	//desactiva todas las balas y asteroides
	//Actualiza las vidas
	void onFighterDeath() {
		AsteroidPool::instance()->disableAll();
		BulletPool::instance()->disableAll();
		mngr_->getGroupEntities(ecs::_grp_Asteroid);
		auto figHealth = GETCMP2(mngr_->getHandler(ecs::_hdlr_Fighter), Health);
		auto gS = GETCMP2(mngr_->getHandler(ecs::_hdlr_GameState), GameState);
		figHealth->takeLife();
		figHealth->isAlive() ? gS->setCurrState(STATE::STOPPED) : gS->setCurrState(STATE::FINISHED);
	}

	//Cuando se queda sin asteroides que disparar
	void onAsteroidsExtenction() {
		auto gS = GETCMP2(mngr_->getHandler(ecs::_hdlr_GameState), GameState);
		gS->setCurrState(STATE::FINISHED);
	}

};

