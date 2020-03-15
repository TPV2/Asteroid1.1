#pragma once

#include "ecs.h"
#include "StarsSystem.h"
#include "System.h"
#include "Score.h"

#include "AsteroidsSystem.h"



class GameCtrlSystem: public System {
private:
	const int START_ASTEROIDS = 10;
public:

	GameCtrlSystem() :
		System(ecs::_sys_GameCtrl) {
	}

	// -crear una entidad, añade sus componentes(Score y GameState) y asociarla
	// con el handler _hndlr_GameState.
	void init() override {
		Entity *e = mngr_->addEntity();
		auto sc = e->addComponent<Score>();
		sc->points_ = 0;
		mngr_->setHandler(ecs::_hdlr_GameState,e);
	}

	// - si el juego está parado y el jugador pulsa ENTER empieza una nueva ronda:
	// 1) añadir 10 asteroides llamando a addAsteroids del AsteroidsSystem.
	// 2) actualizar el estado del juego y el número de vidas (si es necesario)
	// en los componentes correspondientes (Score, Heath, GameState, …).
	void update() override {
		auto ih = game_->getInputHandler();

		if ( ih->keyDownEvent() && ih->isKeyDown(SDLK_RETURN)) {
			mngr_->getSystem<AsteroidsSystem>(ecs::_sys_Asteroids)->addAsteroids(START_ASTEROIDS);
		}
	}

	// - a este método se le va a llamar cuando muere el caza.
	// - desactivar todos los asteroides y las balas.
	// - actualizar los componentes correspondientes (Score, Heath, GameState, …).
	void onFighterDeath() {

	}

	// - a este método se le va a llamar cuando muere el caza.
	// - desactivar todos los asteroides y las balas.
	// - actualizar los componentes correspondientes (Score, GameState, …).
	void onAsteroidsExtenction() {

	}

};

