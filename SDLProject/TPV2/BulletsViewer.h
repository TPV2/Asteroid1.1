#pragma once
#include "Component.h"
#include "BulletsPool.h"
#include "Bullet.h"

class BulletsViewer :
	public Component
{
private:
	Texture* texture_ = nullptr;
	BulletsPool* pool_ = nullptr;
public:
	BulletsViewer(Texture* texture) :
		Component(ecs::BulletsViewer), texture_(texture), pool_(nullptr) {}
	~BulletsViewer() { pool_ = nullptr; };
	void init()override;
	void draw()override;
};

