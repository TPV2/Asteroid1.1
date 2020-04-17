#pragma once
#include "System.h"
#include "Entity.h"
#include "Manager.h"
#include "BulletPool.h"
#include "InputHandler.h"
#include "GameCtrlSystem.h"
#include "Score.h"

class BulletSystem : public System {
	
public:
	BulletSystem() :System(ecs::_sys_Bullets) {};
	
	//Dispara un proyectil
	void shoot(Vector2D pos, Vector2D vel, double width, double height, double rot) {
		Entity* newBullet = mngr_->addEntity<BulletPool>(pos, vel, width, height, rot);
		if (newBullet != nullptr) {
			newBullet->addToGroup(ecs::_grp_Bullet);
		}
	}
	
//Desactiva la bala y agrega los puntos
	void onCollisionWithAsteroid(Entity* b) {
		b->setActive(false);
		GETCMP2(mngr_->getHandler(ecs::_hdlr_GameState), Score)->addPoints(10);
	}
	
	//Mueve las balas y las desactiva si salen de la pantalla && aplica esto solo si esta en modo started
	void update() override {

		if (GETCMP2(mngr_->getHandler(ecs::_hdlr_GameState), GameState)->getCurrSTate() != STATE::STARTED) { return; };

		for (auto& currBullet : mngr_->getGroupEntities(ecs::_grp_Bullet)) {

			if (!currBullet->isActive())
				return;

			Transform* tr = currBullet->getComponent<Transform>(ecs::Transform);

			//Si la bala sale de la pantalla
			if (tr->position_.getX() > game_->getWindowWidth() ||
				tr->position_.getX() < 0.0 ||
				tr->position_.getY() > game_->getWindowHeight() ||
				tr->position_.getY() < 0.0) {
				tr->velocity_.set({ 0,0 });		//Se deja de mover
				currBullet->setActive(false);	//Se desactiva
			}
			else
			{
				Vector2D currPos = { tr->position_.getX() + tr->velocity_.getX() * 2 ,
				tr->position_.getY() + tr->velocity_.getY() * 2 };
				tr->position_.set(currPos);
			}

		}
	}
};


