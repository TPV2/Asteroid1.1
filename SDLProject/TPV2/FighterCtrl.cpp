#include "FighterCtrl.h"
#include "Entity.h"
#include "InputHandler.h"
#include "Transform.h"
#include <math.h>

//Inicializador vacío
FighterCtrl::FighterCtrl(): 
	FighterCtrl(SDLK_RIGHT, SDLK_LEFT,SDLK_UP){}

//Constructor con teclas
FighterCtrl::FighterCtrl(SDL_Keycode right, SDL_Keycode left, SDL_Keycode up) :
	Component(ecs::FighterCtrl),tr_(nullptr),right_(right),left_(left),up_(up){}

FighterCtrl::~FighterCtrl() {
	tr_ = nullptr;
}

void FighterCtrl::init() {
	tr_ = GETCMP1_(Transform);
}

void FighterCtrl::update() {
	InputHandler* ih = InputHandler::instance();
	if (ih->keyDownEvent()) {
		if (ih->isKeyDown(right_)) {
			tr_->setRot(tr_->getRot() + ANGLE_VEL);
		}
		else if (ih->isKeyDown(left_)) {
			tr_->setRot(tr_->getRot() - ANGLE_VEL);
		}
		else if (ih->isKeyDown(up_)) {	//Impulso * cos(ang) = x y sin = y
			Vector2D vel = { tr_->getVel() + Vector2D(0,-1).rotate(tr_->getRot()) * IMPULSE };
			if (vel.magnitude() > MAX_SPEED) {
				vel = vel.normalize() * IMPULSE;
			}
			tr_->setVel(vel);
			//tr_->setVel({ IMPULSE * sin(M_PI* tr_->getRot() / 180.0f), - (IMPULSE * cos(M_PI * tr_->getRot() / 180.0) )});
		}
	}
	else {
		if ((tr_->getVel().getX() != 0.0) || (tr_->getVel().getY() != 0.0)) {
			tr_->setVel({ DECREASE_VEL * tr_->getVel().getX(), DECREASE_VEL * tr_->getVel().getY() });
		}
	}
}
