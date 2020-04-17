#pragma once

#include "Collisions.h"
#include "System.h"
#include "Manager.h"
#include "AsteroidsSystem.h"
#include "FighterSystem.h"
#include "Transform.h"
#include "BulletSystem.h"

class CollisionSystem: public System {
public:
	CollisionSystem() :
		System(ecs::_sys_Collisions) {
	}

	void update() {
		if (mngr_->getHandler(ecs::_hdlr_Fighter)->isActive()) {
			auto figTr = mngr_->getHandler(ecs::_hdlr_Fighter)->getComponent<Transform>(ecs::Transform);	//planeTransform
			for (auto& currAsteroid : mngr_->getGroupEntities(ecs::_grp_Asteroid)) {
				if (currAsteroid->isActive())
				{
					auto etr = currAsteroid->getComponent<Transform>(ecs::Transform);	//asteroidTransform
					//Comprueba la colision entre los asteroides y el avión
					if (Collisions::collides(figTr->position_, figTr->width_, figTr->height_, etr->position_, etr->width_, etr->height_)) {
						game_->getAudioMngr()->playChannel(Resources::Lose, 0, 4);
						mngr_->getSystem<AsteroidsSystem>(ecs::_grp_Asteroid)->onCollision(currAsteroid);
						mngr_->getSystem<FighterSystem>(ecs::_sys_Fighter)->onCollisionWithAsteroid();	//Pierde una vida
						return;
					}

					//Comprueba la colisión entre las balas y los asteroides
					for (auto& currBullet : mngr_->getGroupEntities(ecs::_grp_Bullet)) {
						if (currBullet->isActive())
						{
							auto bulletTr = currBullet->getComponent<Transform>(ecs::Transform);	//bulletTransform
							if (Collisions::collides(bulletTr->position_, bulletTr->width_, bulletTr->height_, etr->position_, etr->width_, etr->height_)) {
								mngr_->getSystem<AsteroidsSystem>(ecs::_sys_Asteroids)->onCollisionWithBullet(currAsteroid);	//Divide el meteorito en 2
								mngr_->getSystem<BulletSystem>(ecs::_sys_Bullets)->onCollisionWithAsteroid(currBullet);		//Desactiva la bala
							}
						}
					}

					//Comprueba colisiones entre asteroides
					for (auto& otherAst : mngr_->getGroupEntities(ecs::_grp_Asteroid)) {
						if (otherAst->isActive() && otherAst != currAsteroid){
							auto otherTr = otherAst->getComponent<Transform>(ecs::Transform);
							if (Collisions::collides(otherTr->position_, otherTr->width_, otherTr->height_, etr->position_, etr->width_, etr->height_)) {
								mngr_->getSystem<AsteroidsSystem>(ecs::_sys_Asteroids)->onCollisionAsteroid(currAsteroid,otherTr->velocity_);
								mngr_->getSystem<AsteroidsSystem>(ecs::_sys_Asteroids)->onCollisionAsteroid(otherAst,etr->velocity_);	
							}
						}

					}
				}

			}
		}

	}
};

