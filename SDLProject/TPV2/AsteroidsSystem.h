#pragma once
#include "System.h"
#include "Entity.h"
#include "Manager.h"
#include "Transform.h"
#include "AsteroidPool.h"

class AsteroidsSystem :
	public System
{
public:
	AsteroidsSystem() :
		System(ecs::_sys_Asteroids) {}

	//Gestiona la colisión de un asteroide
	void onCollision(Entity* e) {
		e->setActive(false);
		Transform* tr = e->getComponent<Transform>(ecs::Transform);
		tr->position_.set({ 0,0 });
		tr->velocity_.set({ 0,0 });
		tr->rotation_ = 0;
		tr->height_ = 0;
		tr->width_ = 0;
	}

	//Crea asteroides en posiciones aleatorias y los mete al grupo de asteroides
	void addAsteroids(std::size_t n) {
		for (auto i(0u); i < n; i++) {
			int r = game_->getRandGen()->nextInt(1, 2);
			Vector2D pos = { (double)game_->getRandGen()->nextInt(0 , game_->getWindowWidth()),
				(double)game_->getRandGen()->nextInt(0, game_->getWindowHeight()) };
			Vector2D scale = { (double)game_->getRandGen()->nextInt(25, 50),0 };
			scale.setY(scale.getX());
			Vector2D speed = { (double)game_->getRandGen()->nextInt(-2.5 , 2.5),
				(double)game_->getRandGen()->nextInt(-2.5 , 2.5) };
			Entity* e = mngr_->addEntity<AsteroidPool>(pos, scale, speed, r);
			if (e != nullptr)
				e->addToGroup(ecs::_grp_Asteroid);
		}
	}


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
	
};

