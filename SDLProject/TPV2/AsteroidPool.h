#pragma once
#include "Singleton.h"
#include "Entity.h"
#include "ObjectPool.h"
#include "Transform.h"
#include "LifeTime.h"
#include "Rotation.h"
#include "ImageComponent.h"
//Componentes para los asteroides


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

	//Constructor de asteroides
	inline Entity* construct_(Vector2D pos, Vector2D scale, Vector2D speed, int rotation) {
		Entity* currAsteroid = pool_.getObj();
		if (currAsteroid != nullptr) {
			currAsteroid->setActive(true);
			Transform* tr = currAsteroid->getComponent<Transform>(ecs::Transform);
			tr->position_.set(pos);
			tr->velocity_.set(speed);
			tr->width_ = scale.getX();
			tr->height_ = scale.getY();
			tr->velocity_.set(speed);
			currAsteroid->getComponent<Rotation>(ecs::Rotation)->rotation_ = rotation;
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
	//Pool de asteroides
	ObjectPool<Entity> pool_;
	//Constructor por defecto a 10 asterorides
	AsteroidPool() : AsteroidPool(10) {};
	
	//Constructor de los asteroides
	AsteroidPool(std::size_t n) :
		pool_(n) {
		for (Entity* e : pool_.getPool()) {
			e->addComponent<Transform>();
			e->addComponent<Rotation>();
			e->addComponent<ImageComponent>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Asteroid));
		}
	}

};

