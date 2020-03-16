#pragma once
#include "Singleton.h"
#include "BulletPool.h"
#include "ObjectPool.h"
#include "Transform.h"
#include "ImageComponent.h"
#include "Entity.h"


class BulletPool 
	: public Singleton<BulletPool> {
	friend Singleton<BulletPool>;
public:
	//Destructor
	virtual ~BulletPool() {};

	//Destructor de instancia
	inline static void destroy(Entity* p) {
		BulletPool::instance()->destroy_(p);
	}

	//Constructor de asteroides
	inline Entity* construct_(Vector2D pos, Vector2D speed, double width, double height) {
		Entity* currBullet = pool_.getObj();
		if (currBullet != nullptr) {
			#pragma region Transform
			currBullet->setActive(true);
			Transform* tr = currBullet->getComponent<Transform>(ecs::Transform);
			tr->position_.set(pos);
			tr->velocity_.set(speed);
			tr->width_ = width;
			tr->height_ = height;
			#pragma endregion
		}
		return currBullet;
	}

	//Destructor de entidades
	inline void destroy_(Entity* p) {
		pool_.relObj(p);
	}

	//Constructor de instancia
	template<typename...Targs>
	inline static Entity* construct(Targs&&...args) {
		return BulletPool::instance()->construct_(std::forward<Targs>(args)...);
	}
private:
	//Pool de asteroides
	ObjectPool<Entity> pool_;
	//Constructor por defecto a 10 asterorides
	BulletPool() : BulletPool(10) {};

	//Constructor de los asteroides
	BulletPool(std::size_t n) :
		pool_(n) {
		for (Entity* e : pool_.getPool()) {
			e->addComponent<Transform>();
			e->addComponent<ImageComponent>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Bullet));
		}
	}
};

