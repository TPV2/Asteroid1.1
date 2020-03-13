#include "FighterMotion.h"
#include "SDL_macros.h"
#include "Entity.h"


//Aplica las diferentes fuerzas para que el figher se mueva
void FighterMotion::update() {
	//Sale por los laterales
	if (fighterTr_->getPos().getX() < 0.0 || fighterTr_->getPos().getX() + fighterTr_->getW() > game_->getWindowWidth()) {
		fighterTr_->setVel(-fighterTr_->getVel().getX(), fighterTr_->getVel().getY());	//Se cambia la velocidad
		fighterTr_->setRot(-fighterTr_->getRot());										//Se cambia la rotación	
		//Se evita que se quede fuera de los límites de la pantalla (BUG)
		if (fighterTr_->getPos().getX() < 0.0) fighterTr_->setPos(0.0, fighterTr_->getPos().getY());
		else if (fighterTr_->getPos().getX() > game_->getWindowWidth()) fighterTr_->setPos(game_->getWindowWidth(), fighterTr_->getPos().getY());
	} 

	//Sale por los extremos
	if (fighterTr_->getPos().getY() < 0.0 || fighterTr_->getPos().getY() + fighterTr_->getH() > game_->getWindowHeight()) {
		fighterTr_->setVel(fighterTr_->getVel().getX(), -fighterTr_->getVel().getY());	//Se cambia la velocidad
		fighterTr_->setRot(180 - fighterTr_->getRot());									//Se cambia la rotación
		//Se evita que se quede fuera de los límites de la pantalla (BUG)
		if (fighterTr_->getPos().getY() < 0.0) fighterTr_->setPos(fighterTr_->getPos().getX(), 0.0);
		else if (fighterTr_->getPos().getY() > game_->getWindowHeight()) fighterTr_->setPos(fighterTr_->getPos().getX(), game_->getWindowHeight());
	}

	fighterTr_->setPosX(fighterTr_->getPos().getX() + fighterTr_->getVel().getX());
	fighterTr_->setPosY(fighterTr_->getPos().getY() + fighterTr_->getVel().getY());
}