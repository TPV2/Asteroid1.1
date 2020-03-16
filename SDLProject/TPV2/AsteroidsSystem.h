#pragma once
#include "System.h"
#include "Entity.h"
#include "Manager.h"
#include "Transform.h"
#include "AsteroidPool.h"
#include <SDL_stdinc.h> // for Uint32


class AsteroidsSystem :
	public System
{
public:
	AsteroidsSystem() :
		System(ecs::_sys_Asteroids) {}

	//Gestiona la colisión de un asteroide
	void onCollision(Entity* e) {

		Transform* tr = e->getComponent<Transform>(ecs::Transform);
		/*AsteroidLifeTime* alt = e->getComponent<AsteroidLifeTime>(ecs::AsteroidLifeTime);
		alt->level_ -= 1;
		Entity* ast1 = AsteroidPool::instance()->getFistFreeEntity();

		if (ast1 != nullptr && alt->level_ >= 1) {
			ast1->setActive(true);
			Transform* tr1 = ast1->getComponent<Transform>(ecs::Transform);
			tr1->position_.set(tr->position_);
			tr1->velocity_.set({ (double)game_->getRandGen()->nextInt(MIN_SPEED,MAX_SPEED),
				(double)game_->getRandGen()->nextInt(MIN_SPEED,MAX_SPEED) });
			tr1->height_ = tr->height_ - 10;
			tr1->width_ = tr->width_ - 10;
			tr1->rotation_ = game_->getRandGen()->nextInt(1, 2);
			AsteroidLifeTime* alt = ast1->getComponent<AsteroidLifeTime>(ecs::AsteroidLifeTime);
			alt->level_--;
			Uint32 lifeTime = game_->getRandGen()->nextInt(MIN_LIFE_TIME, MAX_LIFE_TIME);
			alt->lifeTime_ = lifeTime * 1000;
			alt->creatiomTime_ = SDLGame::instance()->getTime();
			ast1->addToGroup(ecs::AsteroidPool);
		}*/
		e->setActive(false);
		tr->position_.set({ 0,0 });
		tr->velocity_.set({ 0,0 });
		tr->rotation_ = 0;
		tr->height_ = 0;
		tr->width_ = 0;
	}

	//Crea asteroides en posiciones aleatorias y los mete al grupo de asteroides al inicio del juego
	void addAsteroids(std::size_t n) {
		for (auto i(0u); i < n; i++) {
			int r = game_->getRandGen()->nextInt(1, 2);
			Vector2D pos = { (double)game_->getRandGen()->nextInt(0 , game_->getWindowWidth()),
				(double)game_->getRandGen()->nextInt(0, game_->getWindowHeight()) };
			int level = game_->getRandGen()->nextInt(0, MAX_LEVEL);
			Vector2D scale = { (double)MAX_SCALE - (double)level * 10,(double)MAX_SCALE - (double)level * 10 };
			Vector2D speed{ 0,0 };
			while (speed.getX() == 0) speed.setX(game_->getRandGen()->nextInt(MIN_SPEED, MAX_SPEED));
			while (speed.getY() == 0) speed.setY(game_->getRandGen()->nextInt(MIN_SPEED, MAX_SPEED));

			Uint32 lt = game_->getRandGen()->nextInt(MIN_LIFE_TIME, MAX_LIFE_TIME);

			Entity* e = mngr_->addEntity<AsteroidPool>(pos, scale, speed, r, level, lt);
			if (e != nullptr)
				e->addToGroup(ecs::_grp_Asteroid);
		}
	}

	//Movimiento de los asteroides
	void update()override {

		for (auto& e : mngr_->getGroupEntities(ecs::_grp_Asteroid)) {
			if (!e->isActive()) { return; };
				
			Transform* tr = e->getComponent<Transform>(ecs::Transform);
			if (tr != nullptr) {

				Vector2D newPos = { tr->position_.getX() + tr->velocity_.getX(),
					tr->position_.getY() + tr->velocity_.getY()  };
				tr->position_.set(newPos);
				//Si sale de la pantalla
				if (tr->position_.getX() < 0) tr->position_.set({ (double)game_->getWindowWidth(), tr->position_.getY() });			//Izquierda
				else if (tr->position_.getX() > game_->getWindowWidth()) tr->position_.set({ 0, tr->position_.getY() });			//Derecha

				if (tr->position_.getY() < 0) tr->position_.set({ tr->position_.getX(), (double)game_->getWindowHeight() });		//Arriba
				else if (tr->position_.getY() > game_->getWindowHeight()) tr->position_.set({ tr->position_.getX(), 0 });			//Abajo
			}

		}
	}
private:
	const int MAX_LEVEL = 3;
	const double MIN_SPEED = -2.5;
	const double MAX_SPEED = 2.5;
	const double MIN_SCALE = 30;
	const double MAX_SCALE = 50;
	//En segundos
	const int MIN_LIFE_TIME = 5;
	const int MAX_LIFE_TIME = 10;
};

