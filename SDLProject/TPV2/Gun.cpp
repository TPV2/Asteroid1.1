#include "Gun.h"
#include "Entity.h"

void Gun::init() {
	fighterTr_ = GETCMP1_(Transform);
	lastBullet = -BULLET_DELAY;		//Valor inicial para evitar el delay en la primera bala
}

void Gun::update() {
	InputHandler* ih = InputHandler::instance();
	if (ih->keyDownEvent()) {
		if ((ih->isKeyDown(space_) && (game_->getTime()- lastBullet) > BULLET_DELAY)) {
			Vector2D bulletPos = fighterTr_->getPos() +  Vector2D(fighterTr_->getW() / 2, fighterTr_->getH() / 2) + 
				Vector2D(0, -(fighterTr_->getH() / 2 + 5.0)).rotate(fighterTr_->getRot());

			Vector2D bulletDir = Vector2D(0, -1).rotate(fighterTr_->getRot()) * 2;

			pool_->shoot(bulletPos, bulletDir, fighterTr_->getW(), fighterTr_->getH());
			lastBullet = game_->getTime();
		}
	}
}