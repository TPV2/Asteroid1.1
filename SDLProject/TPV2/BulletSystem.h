#pragma once
#include "System.h"
#include "Entity.h"
#include "Manager.h"
#include "BulletPool.h"
#include "InputHandler.h"

class BulletSystem : public System {
	
public:
	BulletSystem() :System(ecs::_sys_Bullets) {};
	// - añadir una bala al juego, como en la práctica 1 pero usando entidades.
	// - no olvidar añadir la bala al grupo _grp_Bullet
	void shoot(Vector2D pos, Vector2D vel, double width, double height) {
		Entity* newBullet = mngr_->addEntity<BulletPool>(pos, vel, width, height);
		if (newBullet != nullptr) {
			newBullet->addToGroup(ecs::_grp_Bullet);
		}
	}
	// - desactivar la bala “b”
	void onCollisionWithAsteroid(Entity* b, Entity* a) {

	}
	// - si el juego está parado no hacer nada.
	// - mover las balas y desactivar las que se salen de la ventana
	void update() override {

		for (auto& currBullet : mngr_->getGroupEntities(ecs::_grp_Bullet)) {

			if (!currBullet->isActive())
				return;

			Transform* tr = currBullet->getComponent<Transform>(ecs::Transform);

			//Si la bala sale de la pantalla
			if (tr->position_.getX() > game_->getWindowWidth() ||
				tr->position_.getX() < 0.0 ||
				tr->position_.getY() > game_->getWindowHeight() ||
				tr->position_.getY() < 0.0) {
				tr->velocity_.set({ 0,0 });			//Se deja de mover
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


