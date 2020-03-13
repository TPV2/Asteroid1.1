#pragma once
#include "Component.h"
#include "AsteroidsPool.h"
#include "Transform.h"

class AsteroidsMotion :
	public Component
{
private:
	AsteroidsPool* pool_ = nullptr;
public:
	AsteroidsMotion() :
		Component(ecs::AsteroidsMotion), pool_(nullptr) {};
	virtual void update() override;
	virtual void init() override;
};

