#pragma once
#include "Singleton.h"
#include "Entity.h"
#include "ObjectPool.h"

//Componentes para los asteroides
#include "AsteroidLifeTime.h"
#include "Rotation.h"
#include "ImageComponent.h"
#include "Transform.h"
#include <SDL_stdinc.h> // for Uint32


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
	inline Entity* construct_(Vector2D pos, Vector2D scale, Vector2D speed, int rotation, int level, Uint32 lifeTime) {
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
			AsteroidLifeTime* astLifeTime = currAsteroid->getComponent<AsteroidLifeTime>(ecs::AsteroidLifeTime);
			astLifeTime->setLevel(level);
			astLifeTime->setLifeTime(lifeTime * 1000);
			astLifeTime->startTime();
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

	//Devuelve el primer elemento libre dentro del pool
	Entity* getFistFreeEntity() { return pool_.getObj(); };
	
	//Desactiva todos los elementos del pool
	void disableAll() {
		for (auto e : pool_.getPool()) {
			e->setActive(false);
		}
	}

private:
	//Constructor por defecto a 10 asterorides
	static const int INIT_AST = 15;

	//Pool de asteroides
	ObjectPool<Entity> pool_;
	AsteroidPool() : AsteroidPool(INIT_AST) {};
	
	//Constructor de los asteroides
	AsteroidPool(std::size_t n) :
		pool_(n) {
		cout << pool_.getPool().size() << endl;
		for (Entity* e : pool_.getPool()) {
			e->addComponent<Transform>();
			e->addComponent<Rotation>();
			e->addComponent<AsteroidLifeTime>();
			e->addComponent<ImageComponent>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Asteroid));
		}
	}

};

