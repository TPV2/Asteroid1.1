#pragma once
#include "ecs.h"
#include "Manager.h"
#include "ImageComponent.h"
#include "SDL_macros.h"
#include "SDLGame.h"
#include "System.h"
#include "Transform.h"
#include "Entity.h"
#include "Manager.h"
#include "Score.h"
#include "SDLGame.h"
#include "Texture.h"
#include "Health.h"

class RenderSystem: public System {
public:
	RenderSystem() :
			System(ecs::_sys_Render) {
	}

	void draw(Entity *e) {
		Transform *tr = e->getComponent<Transform>(ecs::Transform);
		ImageComponent *img = e->getComponent<ImageComponent>(ecs::ImageComponent);
		SDL_Rect dest =
		RECT(tr->position_.getX(), tr->position_.getY(), tr->width_, tr->height_);
		img->tex_->render(dest, tr->rotation_);
	}

	void drawAsteroid(Entity* e) {
		Transform* tr = e->getComponent<Transform>(ecs::Transform);
		ImageComponent* img = e->getComponent<ImageComponent>(ecs::ImageComponent);
		SDL_Rect dest = RECT(tr->position_.getX(), tr->position_.getY(), tr->width_, tr->height_);
		img->tex_->render(dest, tr->rotation_);

		//CONDICION 1 (sale por la derecha de la pantalla)
		if (tr->position_.getX() + tr->width_ > game_->getWindowWidth()) {
			SDL_Rect rectCond1 = RECT(tr->position_.getX() - game_->getWindowWidth(), tr->position_.getY(), tr->width_, tr->height_);
			img->tex_->render(rectCond1, tr->rotation_);
		}

		//CONDICION 2 (sale por abajo)
		if (tr->position_.getY() + tr->height_ > game_->getWindowHeight()) {
			SDL_Rect rectCond2 = RECT(tr->position_.getX(), tr->position_.getY() - game_->getWindowHeight(), tr->width_, tr->height_);
			img->tex_->render(rectCond2, tr->rotation_);
		}

		//CONDICION 3 (1 y 2 a la vez)
		if ((tr->position_.getX() + tr->width_ > game_->getWindowWidth()) && (tr->position_.getY() + tr->height_ > game_->getWindowHeight())) {
			SDL_Rect rectCond3 = RECT(tr->position_.getX() - game_->getWindowWidth(), tr->position_.getY() - game_->getWindowHeight(), tr->width_, tr->height_);
			img->tex_->render(rectCond3, tr->rotation_);
		}

	}

	void draw(Entity* e,SDL_Rect clip) {
		Transform* tr = e->getComponent<Transform>(ecs::Transform);
		ImageComponent* img = e->getComponent<ImageComponent>(ecs::ImageComponent);
		SDL_Rect dest =
			RECT(tr->position_.getX(), tr->position_.getY(), tr->width_, tr->height_);
		img->tex_->render(dest, tr->rotation_, clip);
	}

	void drawScore() {
		auto sc =
				mngr_->getHandler(ecs::_hdlr_GameState)->getComponent<Score>(ecs::Score);
		Texture scoreMsg(game_->getRenderer(), std::to_string(sc->getPoints()),
				game_->getFontMngr()->getFont(Resources::ARIAL24),
				{ COLOR(0x0000ffff) });
		scoreMsg.render(game_->getWindowWidth() / 2 - scoreMsg.getWidth() / 2,
				10);
	}

	//Renderiza los corazones en función de las vidas que tenga el fighter
	void drawLives() {
		auto figHealth = mngr_->getHandler(ecs::_hdlr_Fighter)->getComponent<Health>(ecs::Health);
		int GAP = 25;
		heartRect.x = HEART_START_X;
		for (int i = 0; i < figHealth->getLives(); i++) {

			auto tex = game_->getTextureMngr()->getTexture(Resources::Heart);	
			tex->render(heartRect);
			heartRect.x += GAP;
		}	
	}

	void update() override {
		// draw asteroids
		for (auto& e : mngr_->getGroupEntities(ecs::_grp_Asteroid)) {
			drawAsteroid(e);
		}

		//Draw bullets
		for (auto& e : mngr_->getGroupEntities(ecs::_grp_Bullet)) {
			draw(e);
		}
		
		//Draw fighter
		draw(mngr_->getHandler(ecs::_hdlr_Fighter), planeRect);
		

		// draw score
		drawScore();

		// draw lives
		drawLives();

		// info message
		Texture msg(game_->getRenderer(),"Press ENTER to add More Stars", game_->getFontMngr()->getFont(Resources::ARIAL24),{COLOR(0xff0000ff)});
		msg.render(game_->getWindowWidth()/2-msg.getWidth()/2,game_->getWindowHeight()-msg.getHeight()-10);
	}
private:
	SDL_Rect planeRect = RECT(47,90,207,250);
	SDL_Rect heartRect = RECT(10, 10, 25, 25);
	const int HEART_START_X = 10;
};

