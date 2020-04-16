#pragma once
#include "System.h"
#include "InputHandler.h"
#include "Manager.h"
#include "FighterSystem.h"
#include "Transform.h"
#include "GameState.h"

class FighterGun :
	public System
{
private:
	//Tiempo en milisegundos que hay entre disparos
	Uint32 shootDelay = 2500;
	//Representa el ultimo disparo que se hizo
	Uint32 lastShoot = 0;
	//Valor del ancho de la bala
	const double BULLET_W = 14;
	//Valor del alto de la bala
	const double BULLET_H = 50;
	//Bool que representa si se está escuchando el sonido del error
	bool errorPlay = false;
public:
	//constructor del fighterGun
	FighterGun():
		System(ecs::_sys_FighterGun) {
		resetShootTime();
	};

	//Se encarga de crear las balas
	void update() override {
		auto ih = InputHandler::instance();
		auto gS = GETCMP2(mngr_->getHandler(ecs::_hdlr_GameState), GameState);

		if (gS->getCurrSTate() == STATE::STARTED && ih->keyDownEvent() && ih->isKeyDown(SDLK_SPACE)) {
			if (canShoot()) {
				game_->getAudioMngr()->playChannel(Resources::Rocket, 0, 0);
				game_->getAudioMngr()->setChannelVolume(7, 0);
				lastShoot = game_->getTime();
				auto figTr = GETCMP2(mngr_->getHandler(ecs::_hdlr_Fighter), Transform);
				Vector2D bulletPos = figTr->position_ + Vector2D((figTr->width_ / 2) - (BULLET_W / 2), 0) +
					Vector2D(0, -(figTr->height_ / 2 + 5.0)).rotate(figTr->rotation_);
				Vector2D bulletDir = Vector2D(0, -1).rotate(figTr->rotation_) * 2;
				mngr_->getSystem<BulletSystem>(ecs::_sys_Bullets)->shoot
				(bulletPos, bulletDir, BULLET_W, BULLET_H, figTr->rotation_);
			}
			else
			{
				game_->getAudioMngr()->playChannel(Resources::Error,0,2);
			}
		}
	}

	//Devuelve true si el figher puede disparar
	bool canShoot() {
		return lastShoot + shootDelay <= game_->getTime() ? true : false;
	}

	//Resetea el tiempo para poder volver a disparar
	void resetShootTime() {
		lastShoot = game_->getTime() - shootDelay;
	}
};

