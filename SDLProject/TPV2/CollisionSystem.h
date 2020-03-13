#pragma once

#include "Collisions.h"
#include "System.h"
#include "Manager.h"
#include "StarsSystem.h"
#include "Transform.h"

class CollisionSystem: public System {
public:
	CollisionSystem() :
		System(ecs::_sys_Collisions) {
	}

	void update() {
		auto ptr = mngr_->getHandler(ecs::_hdlr_PacMan)->getComponent<Transform>(ecs::Transform);
		for( auto& e : mngr_->getGroupEntities(ecs::_grp_Star)) {
			auto etr = e->getComponent<Transform>(ecs::Transform);
			if ( Collisions::collides(ptr->position_, ptr->width_, ptr->height_, etr->position_, etr->width_, etr->height_)) {
				mngr_->getSystem<StarsSystem>(ecs::_sys_Stars)->onCollision(e);
			}
		}
	}
};

