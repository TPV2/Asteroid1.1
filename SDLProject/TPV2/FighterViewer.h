#pragma once
#include "Component.h"
#include "Transform.h"
#include <SDL_rect.h>

#pragma region const
const uint SPRITESHEET_PLANE_X = 47;
const uint SPRITESHEET_PLANE_Y = 90;
const int SPRITESHEET_PLANE_W = 207;
const int SPRITESHEET_PLANE_H = 250;
const double GAME_PLANE_W = 41.4;
const double GAME_PLANE_H = 50;
#pragma endregion


//class Transform;
class Texture;

class FighterViewer :
	public Component
{
private:
	Texture* texture_ = nullptr;		//Textura con todos los aviones
	Transform* tr_ = nullptr;			//puntero al transform del objeto
public:
	FighterViewer(Texture* texture_);
	~FighterViewer();
	void init() override;
	void draw() override;
};

