#pragma once
#include "Component.h"
#include "ObjectPool.h"
#include "Asteroid.h"

#pragma region Constantes
const uint ASTEROID_NUM = 30;
const int SAFE_ZONE_W = 200;
const int SAFE_ZONE_H = 150;
#pragma endregion

class Bullet;

class AsteroidsPool : public Component
{
private:
	ObjectPool<Asteroid, ASTEROID_NUM> astPool;
	int asteroidsActive = 0;
public:
	AsteroidsPool();
	void generateAsteroids(int n);
	void disablAll();
	void onCollision( Asteroid* a);
	const int getNumOfAsteroids() { return asteroidsActive; };
	vector<Asteroid*> getPool() { return astPool.getPool(); };
	bool validPosition(const Vector2D& astPos);
};

