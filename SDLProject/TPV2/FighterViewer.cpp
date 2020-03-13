#include "FighterViewer.h"
#include "Texture.h"
#include "Resources.h"
#include "Entity.h"
#include "SDL_macros.h"




FighterViewer::FighterViewer(Texture* texture) :
	Component(ecs::FighterViewer),
	tr_(nullptr), texture_(texture) {
}

FighterViewer::~FighterViewer() {
	
}

//Inicializa el render del avión con los datos dados por el enunciado
void FighterViewer::init() {
	tr_ = GETCMP1_(Transform);
	//Se le dan los tamaños
	tr_->setWH(GAME_PLANE_W, GAME_PLANE_H);
	tr_->setPos({ double((game_->getWindowWidth() - GAME_PLANE_W) / 2),double((game_->getWindowHeight() - GAME_PLANE_H) / 2) });
}

//Renderiza el fighter
void FighterViewer::draw() {
	SDL_Rect destRect = RECT(tr_->getPos().getX(), tr_->getPos().getY(), tr_->getW(), tr_->getH());
	SDL_Rect clipRect = RECT(SPRITESHEET_PLANE_X, SPRITESHEET_PLANE_Y, SPRITESHEET_PLANE_W, SPRITESHEET_PLANE_H);	//Este es el SDL_Rect que coje la parte del Spritesheet que se va a mostrar
	texture_->render(destRect, tr_->getRot(), clipRect);
}
