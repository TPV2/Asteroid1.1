#pragma once

#include <cmath>
#include "SDL_macros.h"
#include "LifeTime.h"
#include "System.h"
#include "Transform.h"
#include "Entity.h"
#include "Rotation.h"
#include "StarsPool.h"
#include "Manager.h"
#include "Score.h"
#include "SDLGame.h"



class StarsSystem: public System {
public:
	StarsSystem() :
			System(ecs::_sys_Stars) {
	}

	void onCollision(Entity *s) {
		s->setActive(false);
		auto sc = mngr_->getHandler(ecs::_hdlr_GameState)->getComponent<Score>(ecs::Score);
		sc->points_++;
	}

	void addStars(std::size_t n) {
		for (auto i(0u); i < n; i++) {
			int x = game_->getRandGen()->nextInt(0, game_->getWindowWidth());
			int y = game_->getRandGen()->nextInt(0, game_->getWindowHeight());
			int w = game_->getRandGen()->nextInt(25, 50);
			int h = w;
			int r = game_->getRandGen()->nextInt(1, 2);
			Uint32 lt = game_->getRandGen()->nextInt(5, 10);

			Entity *e = mngr_->addEntity<StarsPool>(x, y, w, h, r, lt);
			if (e != nullptr)
				e->addToGroup(ecs::_grp_Star);
		}
	}

	void update() override {
		for (auto &e : mngr_->getGroupEntities(ecs::_grp_Star)) {

			if ( !e->isActive() )
				return;

			Transform *tr = e->getComponent<Transform>(ecs::Transform);
			LifeTime *st = e->getComponent<LifeTime>(ecs::LifeTime);
			auto *rot = e->getComponent<Rotation>(ecs::Rotation);
			tr->position_ = tr->position_ + tr->velocity_;
			tr->rotation_ += rot->rotation_;

			if (game_->getTime() - st->creatiomTime_ > st->lifeTime_) {
				e->setActive(false);

				for (int i = 0; i < 2; i++) {
					int x = game_->getRandGen()->nextInt(0,
							game_->getWindowWidth());
					int y = game_->getRandGen()->nextInt(0,
							game_->getWindowHeight());
					int w = game_->getRandGen()->nextInt(25, 50);
					int h = w;
					int r = game_->getRandGen()->nextInt(1, 2);
					Uint32 lt = game_->getRandGen()->nextInt(5, 10);

					Entity *e = mngr_->addEntity<StarsPool>(x, y, w, h, r, lt);
					if (e != nullptr)
						e->addToGroup(ecs::_grp_Star);
				}

			}

		}

	}
};

