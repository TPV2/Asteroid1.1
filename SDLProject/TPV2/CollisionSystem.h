#pragma once

#include "Collisions.h"
#include "System.h"
#include "Manager.h"
#include "AsteroidsSystem.h"
#include "FighterSystem.h"
#include "Transform.h"

class CollisionSystem: public System {
public:
	CollisionSystem() :
		System(ecs::_sys_Collisions) {
	}

	void update() {
		if (mngr_->getHandler(ecs::_hdlr_Fighter)->isActive()) {
			auto ptr = mngr_->getHandler(ecs::_hdlr_Fighter)->getComponent<Transform>(ecs::Transform);	//planeTransform
			for (auto& e : mngr_->getGroupEntities(ecs::_grp_Asteroid)) {
				if (e->isActive())
				{
					auto etr = e->getComponent<Transform>(ecs::Transform);	//asteroidTransform

					//Comprueba la colision entre los asteroides y el avión
					if (Collisions::collides(ptr->position_, ptr->width_, ptr->height_, etr->position_, etr->width_, etr->height_)) {
						mngr_->getSystem<AsteroidsSystem>(ecs::_grp_Asteroid)->onCollision(e);
						mngr_->getSystem<FighterSystem>(ecs::_sys_Fighter)->onCollisionWithAsteroid();	//Pierde una vida
					}

					//Comprueba la colisión entre las balas y los asteroides
					for (auto& b : mngr_->getGroupEntities(ecs::_grp_Bullet)) {
						if (b->isActive())
						{
							auto btr = b->getComponent<Transform>(ecs::Transform);	//bulletTransform
							if (Collisions::collides(btr->position_, btr->width_, btr->height_, etr->position_, etr->width_, etr->height_)) {
								mngr_->getSystem<AsteroidsSystem>(ecs::_grp_Asteroid)->onCollisionWithBullet(e);	//Divide el meteorito en 2
								mngr_->getSystem<BulletSystem>(ecs::_sys_Bullets)->onCollisionWithAsteroid(b);		//Desactiva la bala
							}
						}
					}
				}

			}
		}

	}
};

