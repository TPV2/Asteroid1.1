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
			auto ptr = mngr_->getHandler(ecs::_hdlr_Fighter)->getComponent<Transform>(ecs::Transform);
			for (auto& e : mngr_->getGroupEntities(ecs::_grp_Asteroid)) {
				auto etr = e->getComponent<Transform>(ecs::Transform);
				if ( Collisions::collides(ptr->position_, ptr->width_, ptr->height_, etr->position_, etr->width_, etr->height_)) {
					mngr_->getSystem<AsteroidsSystem>(ecs::_grp_Asteroid)->onCollision(e);
					mngr_->getSystem<FighterSystem>(ecs::_sys_Fighter)->onCollisionWithAsteroid();
				}
			}
		}

	}
};

