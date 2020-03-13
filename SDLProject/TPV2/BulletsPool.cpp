#include "BulletsPool.h"

BulletsPool::BulletsPool() :
	Component(ecs::BulletsPool),
	obPool([](Bullet* a) {return a->isUsed(); }) {};

//Desactiva todos los elementos del pool
void BulletsPool::disablAll() {
	for (auto it = obPool.getPool().begin(); it != obPool.getPool().end(); ++it) {
		(*it)->setObject(false);
	}
}

//Desactiva al bullet que le pasan por parámetro
void BulletsPool::onCollision(Bullet* b) {
	b->setObject(false);
}

//pide el primer objeto no usado del pool, si es distinto de null lo inicializa
void BulletsPool::shoot(Vector2D pos, Vector2D dir, double w, double h) {
	auto currBullet = obPool.getObj();
	if (currBullet != nullptr) {
		game_->getAudioMngr()->playChannel(Resources::Shoot, 0);
		currBullet->startBullet(pos, dir);
	}
}