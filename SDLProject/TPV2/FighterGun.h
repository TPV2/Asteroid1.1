#pragma once
#include "System.h"
#include "InputHandler.h"
#include "Manager.h"
#include "FighterSystem.h"
#include "Transform.h"

class FighterGun :
	public System
{
public:

	FighterGun():
		System(ecs::_sys_FighterGun){};
	
	// - si el juego está parado no hacer nada.
	// - si el jugador pulsa SPACE, llamar a shoot(...) del BulletsSystem para añadir
	// una bala al juego -- se puede disparar sólo una bala cada 0.25sec.
	void update() override {
		auto ih = InputHandler::instance();
		if (ih->keyDownEvent()) {
			if (ih->isKeyDown(SDLK_SPACE)) {
				auto tr = mngr_->getSystem<FighterSystem>(ecs::_sys_Fighter)->getTranform();
				Vector2D bulletPos = tr->position_ + Vector2D(tr->width_ / 2, tr->height_ / 2) +
					Vector2D(0, -(tr->height_ / 2 + 5.0)).rotate(tr->rotation_);

				Vector2D bulletDir = Vector2D(0, -1).rotate(tr->rotation_) * 2;
				//lastBullet = game_->getTime();
				mngr_->getSystem<BulletSystem>(ecs::_sys_Bullets)->shoot(bulletPos, bulletDir, 50, 50);
			}
		}
	}
};

