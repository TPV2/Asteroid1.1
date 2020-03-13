#include "Health.h"

Health::Health(Texture* texture) :
	Component(ecs::Health), texture_(texture) {}

Health::~Health() {
	delete destRect_;
}

void Health::init() {
	destRect_ = new SDL_Rect({ HEART_X,HEART_Y,HEART_W,HEART_H });
}

void Health::draw() {
	uint gap = 0;
	for (int i = 0; i < lives_; i++) {
		texture_->render({ (int)(HEART_X + gap),HEART_Y,HEART_W,HEART_H });
		gap += HEART_GAP;
	}
}

void Health::removeLives(int amount) {
	lives_ -= amount;
}

