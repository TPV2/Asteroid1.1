#pragma once

#include "Component.h"
#include "ScoreManager.h"
#include "Transform.h"
#include "AsteroidsPool.h"
#include "Health.h"

#pragma region Constantes
const int ASTEROIDS_NUM = 10;
#pragma endregion


class GameCtrl: public Component {
public:
	GameCtrl(AsteroidsPool* astPool, Health* health) :
		Component(ecs::GameCtrl), astPool_(astPool), health_(health), scoreManager_(nullptr) {}
	virtual ~GameCtrl();
	void init() override;
	void update() override;
	void draw() override;
private:
	AsteroidsPool* astPool_;
	Health* health_;
	ScoreManager* scoreManager_;
};

