#pragma once
#include "Component.h"

struct Score: Component {
private:
	unsigned int points_;
public:
	Score() :
		Component(ecs::Score), points_(0) {};
	inline const int getPoints() { return points_; };
	inline void addPoints(int value) { points_ += value; };
	inline void resetPoints() { points_ = 0; };
};

