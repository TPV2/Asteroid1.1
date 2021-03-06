#pragma once
#include "System.h"
#include "Entity.h"
#include "Transform.h"
#include "Manager.h"
#include "ImageComponent.h"
//#include "BulletSystem.h"
//revisados
#include "Health.h"
#include "GameCtrlSystem.h"


const int IMPULSE = 10;
const int ANGLE_VEL = 12;
const double DECREASE_VEL = 0.97;

class FighterSystem :
	public System
{
public:
	//Constructor del fighter
	FighterSystem() :
		System(ecs::_sys_Fighter),
		fighter_(nullptr),
		tr_(nullptr) {};
	
	//Inicializa al fighter
	void init() override {
		fighter_ = mngr_->addEntity();
		tr_ = fighter_->addComponent<Transform>(Vector2D(100.0, 100), Vector2D(), 50, 50, 0);
		fighter_->addComponent<ImageComponent>(game_->getTextureMngr()->getTexture(Resources::Fighter));
		fighter_->addComponent<Health>();
		mngr_->setHandler(ecs::_hdlr_Fighter, fighter_);
		inputHandler_ = InputHandler::instance();
		audioManager_ = game_->getAudioMngr();
		resetFighter();
	}

	//Gestiona los efectos que produce colisionar contra un asteroide
	void onCollisionWithAsteroid() {
		resetFighter();
		mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl)->onFighterDeath();
	}

	//Resetea el transform del fighter centrando la posici�n y poniendo la velocidad a cero
	void resetFighter() {
		tr_->position_.set({ (double)(game_->getWindowWidth() / 2) - (tr_->width_ / 2),
			(double)(game_->getWindowHeight() / 2) - (tr_->height_ / 2) });
		tr_->velocity_.set({ 0,0 });
		tr_->rotation_ = 0;
	}

	//Recibe el input, gestiona el movimiento del fighter y  comprueba las colsiones con los bordes
	void update() override {
		assert(tr_ != nullptr);
		if (inputHandler_->keyDownEvent()) {
			//Tecla a la derecha
			if (inputHandler_->isKeyDown(SDLK_RIGHT)) {
				tr_->rotation_ += ANGLE_VEL;
			}
			//Tecla a la izquierda
			else if (inputHandler_->isKeyDown(SDLK_LEFT)) {
				tr_->rotation_ -= ANGLE_VEL;
			}
			//Tecla hacia arriba
			else if (inputHandler_->isKeyDown(SDLK_UP)) {
				audioManager_->playChannel(Resources::Propulsion, 0, (int)EFFECTS::Movement);
				audioManager_->setChannelVolume(5, 3);
				tr_->velocity_.set(Vector2D({ IMPULSE * sin(M_PI * tr_->rotation_ / 180.0f), -(IMPULSE * cos(M_PI * tr_->rotation_ / 180.0)) }));
			}
		}
		//Se decrece la velocidad
		else {
			if ((tr_->velocity_.getX() != 0.0) || (tr_->velocity_.getY() != 0.0)) {
				tr_->velocity_.set(Vector2D({ DECREASE_VEL * tr_->velocity_.getX(), DECREASE_VEL * tr_->velocity_.getY() }));
			}
		}
		
		//Sale por los laterales
		if (tr_->position_.getX() < 0.0 || tr_->position_.getX() + tr_->width_ > game_->getWindowWidth()) {
			audioManager_->playChannel(Resources::Rebound, 0, 7);
			audioManager_->setChannelVolume(6, 7);
			tr_->velocity_.set(-tr_->velocity_.getX(), tr_->velocity_.getY());		//Se cambia la velocidad
			tr_->rotation_ = -tr_->rotation_;										//Se cambia la rotaci�n	
			//Se evita que se quede fuera de los l�mites de la pantalla (BUG)
			if (tr_->position_.getX() < 0.0) tr_->position_.set(0.0, tr_->position_.getY());
			else if (tr_->position_.getX() > game_->getWindowWidth()) tr_->position_.set(game_->getWindowWidth(), tr_->position_.getY());
		}

		//Sale por los extremos
		if (tr_->position_.getY() < 0.0 || tr_->position_.getY() + tr_->height_ > game_->getWindowHeight()) {
			audioManager_->playChannel(Resources::Rebound, 0, 7);
			audioManager_->setChannelVolume(6, 7);
			tr_->velocity_.set(tr_->velocity_.getX(), -tr_->velocity_.getY());		//Se cambia la velocidad
			tr_->rotation_ = (180 - tr_->rotation_);								//Se cambia la rotaci�n
			//Se evita que se quede fuera de los l�mites de la pantalla (BUG)
			if (tr_->position_.getY() < 0.0) tr_->position_.set(tr_->position_.getX(), 0.0);
			else if (tr_->position_.getY() > game_->getWindowHeight()) tr_->position_.set(tr_->position_.getX(), game_->getWindowHeight());
		}

		tr_->position_.setX(tr_->position_.getX() + tr_->velocity_.getX());
		tr_->position_.setY(tr_->position_.getY() + tr_->velocity_.getY());
	}
private:
	Entity* fighter_ = nullptr;
	Transform* tr_ = nullptr;
	InputHandler* inputHandler_ = nullptr;
	AudioManager* audioManager_ = nullptr;
};

