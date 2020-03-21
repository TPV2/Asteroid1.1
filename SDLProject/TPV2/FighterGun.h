#pragma once
#include "System.h"
#include "InputHandler.h"
#include "Manager.h"
#include "FighterSystem.h"
#include "Transform.h"
#include "GameState.h"
#include "GameCtrlSystem.h"

class FighterGun :
	public System
{
private:
	Uint32 shootDelay = 2500;
	Uint32 lastShoot;
public:

	FighterGun():
		System(ecs::_sys_FighterGun) {
		lastShoot = game_->getTime();
	};

	
	// - si el juego está parado no hacer nada.
	// - si el jugador pulsa SPACE, llamar a shoot(...) del BulletsSystem para añadir
	// una bala al juego -- se puede disparar sólo una bala cada 0.25sec.
	void update() override {
		auto ih = InputHandler::instance();
		auto gS = GETCMP2(mngr_->getHandler(ecs::_hdlr_GameState), GameState);

		if (gS->getCurrSTate() == STATE::STARTED && ih->keyDownEvent()) {
			if (ih->isKeyDown(SDLK_SPACE) && lastShoot + shootDelay <= game_->getTime()) {
				lastShoot = game_->getTime();
				auto figTr = GETCMP2(mngr_->getHandler(ecs::_hdlr_Fighter), Transform);
				Vector2D bulletPos = figTr->position_ + Vector2D(figTr->width_ / 2, figTr->height_ / 2) +
					Vector2D(0, -(figTr->height_ / 2 + 5.0)).rotate(figTr->rotation_);

				Vector2D bulletDir = Vector2D(0, -1).rotate(figTr->rotation_) * 2;
				mngr_->getSystem<BulletSystem>(ecs::_sys_Bullets)->shoot
				(bulletPos, bulletDir, 15, 50, figTr->rotation_);
			}
		}
	}
};

