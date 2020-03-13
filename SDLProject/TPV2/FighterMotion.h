#pragma once
#include "Component.h"
#include "Transform.h"

class FighterMotion :
	public Component
{
private:
	Transform* fighterTr_ = nullptr;
public:
	FighterMotion(Transform* tr) :
		Component(ecs::FighterMotion), fighterTr_(tr){};
	virtual void update() override;
};