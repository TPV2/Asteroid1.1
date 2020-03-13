#pragma once
#include "Component.h"
#include "Transform.h"

#pragma region consts
const uint ANGLE_VEL = 12;
const uint IMPULSE = 2.5;
const double DECREASE_VEL = 0.99;
const double MAX_SPEED = 12.5;
#pragma endregion


class FighterCtrl :
	public Component
{
private:
	Transform* tr_;
	SDL_Keycode right_;
	SDL_Keycode left_;
	SDL_Keycode up_;

public:
	FighterCtrl();
	FighterCtrl(SDL_Keycode right, SDL_Keycode left, SDL_Keycode up);
	~FighterCtrl();

	void init() override;
	void update() override;
};

