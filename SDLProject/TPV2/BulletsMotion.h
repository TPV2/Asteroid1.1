#pragma once
#include "Component.h"
#include "BulletsPool.h"
#include "Transform.h"

class BulletsMotion :
	public Component
{
private:
	BulletsPool* pool_ = nullptr;
	Transform* fighterTr_ = nullptr;
public:
	BulletsMotion(Transform* tr) :
		Component(ecs::BulletsMotion), fighterTr_(tr), pool_(nullptr) {};
	virtual void update() override;
	virtual void init() override;
};



