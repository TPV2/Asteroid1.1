#pragma once
#include "Singleton.h"
#include "Entity.h"
#include "ObjectPool.h"
#include "Transform.h"
#include "LifeTime.h"
#include "Rotation.h"
#include "ImageComponent.h"


class AsteroidPool : public Singleton<AsteroidPool>
{
	friend Singleton<AsteroidPool>;
public:
	//Destructor
	virtual ~AsteroidPool() {};

	//Destructor de instancia
	inline static void destroy(Entity* p) {
		AsteroidPool::instance()->destroy_(p);
	}

	//Constructor de entidades
	inline Entity* construct_(double x, double y, double w, double h, double r, Uint32 lifeTime) {
		Entity* currAsteroid = pool_.getObj();
		if (currAsteroid != nullptr) {
			currAsteroid->setActive(true);
			Transform* tr = currAsteroid->getComponent<Transform>(ecs::Transform);
			tr->position_.set(x, y);
			tr->width_ = w;
			tr->height_ = w;
			LifeTime* st = currAsteroid->getComponent<LifeTime>(ecs::LifeTime);
			st->lifeTime_ = lifeTime * 1000;
			st->creatiomTime_ = SDLGame::instance()->getTime();
			currAsteroid->getComponent<Rotation>(ecs::Rotation)->rotation_ = r;
		}
		return currAsteroid;
	}

	//Destructor de entidades
	inline void destroy_(Entity* p) {
		pool_.relObj(p);
	}

	//Constructor de instancia
	template<typename...Targs>
	inline static Entity* construct(Targs&&...args) {
		return AsteroidPool::instance()->construct_(std::forward<Targs>(args)...);
	}
private:
	//Pool de objetos
	ObjectPool<Entity> pool_;
	AsteroidPool() : AsteroidPool(10) {};

	AsteroidPool(std::size_t n) :
		pool_(n) {
		for (Entity* e : pool_.getPool()) {
			e->addComponent<Transform>();
			e->addComponent<LifeTime>();
			e->addComponent<Rotation>();
			e->addComponent<ImageComponent>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Asteroid));
		}
	}

};

