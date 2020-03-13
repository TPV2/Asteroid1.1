#include "BulletsMotion.h"
#include "SDL_macros.h"
#include "Entity.h"


void BulletsMotion::init() {
	pool_ = GETCMP1_(BulletsPool);
}

//Comprueba si un bullet está siendo usado, si es así, modifica la velocidad y posición
void BulletsMotion::update() {

	for (int i = 0; i < pool_->getPool().size(); i++) {
		if (pool_->getPool()[i]->isUsed()) {
			Bullet* currBullet = pool_->getPool()[i];

			//Si la bala sale de la pantalla
			if (currBullet->getPos()->getX() > game_->getWindowWidth() ||
				currBullet->getPos()->getX() < 0.0 ||
				currBullet->getPos()->getY() > game_->getWindowHeight() ||
				currBullet->getPos()->getY() < 0.0) {
				currBullet->setVel(0);			//Se deja de mover
				currBullet->setObject(false);	//Se desactiva
			}
			//Si no sale de la pantalla
			else
			{
				Vector2D currPos = { currBullet->getPos()->getX() + currBullet->getDir()->getX() * currBullet->getVel() ,
				currBullet->getPos()->getY() + currBullet->getDir()->getY() * currBullet->getVel() };

				currBullet->setPos(currPos);
			}
			currBullet = nullptr;
		}
	}
}