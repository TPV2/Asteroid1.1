#pragma once

#include "Component.h"
#include "ScoreManager.h"
#include "Transform.h"
#include "Health.h"
#include "AsteroidsPool.h"
#include "BulletsPool.h"

class GameLogic: public Component {
private:
	Transform* fighterTR_;
	BulletsPool* bullerPool_;
	AsteroidsPool* astPool_;
	Health* health_;
	ScoreManager* scoreManager_;
public:
	GameLogic(Transform* fighterTR, BulletsPool* bulletPool, AsteroidsPool* astPool, Health* health);
	virtual ~GameLogic();
	void init() override;
	void update() override;
	void resetFighter();
};

