#include "AsteroidsViewer.h"
#include "AsteroidsPool.h"
#include "SDL_macros.h"
#include <SDL_rect.h>
#include "Entity.h"

void AsteroidsViewer::init() {
	pool_ = GETCMP1_(AsteroidsPool);
}

//Si un asteroide está siendo usado, se renderiza
void AsteroidsViewer::draw() {
	for (int i = 0; i < pool_->getPool().size(); i++) {
		if (pool_->getPool()[i]->isUsed()) {
			SDL_Rect rect = RECT(pool_->getPool()[i]->getPos()->getX(), pool_->getPool()[i]->getPos()->getY(),
				pool_->getPool()[i]->getW(), pool_->getPool()[i]->getH());	
			texture_->render(rect, pool_->getPool()[i]->getAngle());
			
			//CONDICION 1 (sale por la derecha de la pantalla)
			if (pool_->getPool()[i]->getPos()->getX() + pool_->getPool()[i]->getW() > game_->getWindowWidth()) {
				SDL_Rect rectCond1 = RECT(pool_->getPool()[i]->getPos()->getX() - game_->getWindowWidth(), pool_->getPool()[i]->getPos()->getY(),
					pool_->getPool()[i]->getW(), pool_->getPool()[i]->getH());
				texture_->render(rectCond1, pool_->getPool()[i]->getAngle());
			}

			//CONDICION 2 (sale por abajo)
			if (pool_->getPool()[i]->getPos()->getY() + pool_->getPool()[i]->getH() > game_->getWindowHeight()) {
				SDL_Rect rectCond2 = RECT(pool_->getPool()[i]->getPos()->getX(), pool_->getPool()[i]->getPos()->getY() - game_->getWindowHeight(),
					pool_->getPool()[i]->getW(), pool_->getPool()[i]->getH());
				texture_->render(rectCond2, pool_->getPool()[i]->getAngle());
			}

			//CONDICION 3 (1 y 2 a la vez)
			if ((pool_->getPool()[i]->getPos()->getX() + pool_->getPool()[i]->getW() > game_->getWindowWidth()) && (pool_->getPool()[i]->getPos()->getY() + pool_->getPool()[i]->getH() > game_->getWindowHeight())) {
				SDL_Rect rectCond3 = RECT(pool_->getPool()[i]->getPos()->getX() - game_->getWindowWidth(), pool_->getPool()[i]->getPos()->getY() - game_->getWindowHeight(),
					pool_->getPool()[i]->getW(), pool_->getPool()[i]->getH());
				texture_->render(rectCond3, pool_->getPool()[i]->getAngle());
			}
		}
	}
}