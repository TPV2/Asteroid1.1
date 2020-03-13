#pragma once
#include "Component.h"
#include "AsteroidsPool.h"
#include "Asteroid.h"

class AsteroidsViewer :
	public Component
{
private:
	Texture* texture_ = nullptr;
	AsteroidsPool* pool_ = nullptr;
public:
	AsteroidsViewer(Texture* texture) :
		Component(ecs::AsteroidsViewer), texture_(texture), pool_(nullptr) {}
	~AsteroidsViewer() {  pool_ = nullptr; };
	void init()override;
	void draw()override;
};

