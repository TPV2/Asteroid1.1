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

class RenderSystem: public System {
public:
	RenderSystem() :
			System(ecs::_sys_Render) {
	}

	void draw(Entity *e) {
		Transform *tr = e->getComponent<Transform>(ecs::Transform);
		ImageComponent *img = e->getComponent<ImageComponent>(ecs::ImageComponent);
		SDL_Rect dest =
		RECT(tr->position_.getX(), tr->position_.getY(), tr->width_,
				tr->height_);
		img->tex_->render(dest, tr->rotation_);
	}

	void drawScore() {
		auto sc =
				mngr_->getHandler(ecs::_hdlr_GameState)->getComponent<Score>(ecs::Score);
		Texture scoreMsg(game_->getRenderer(), std::to_string(sc->points_),
				game_->getFontMngr()->getFont(Resources::ARIAL24),
				{ COLOR(0x0000ffff) });
		scoreMsg.render(game_->getWindowWidth() / 2 - scoreMsg.getWidth() / 2,
				10);

	}

	void update() override {

		// draw stars
		for (auto &e : mngr_->getGroupEntities(ecs::_grp_Star)) {
			draw(e);
		}

		// draw pacman
		draw(mngr_->getHandler(ecs::_hdlr_PacMan));

		// draw score
		drawScore();

		// info message
		Texture msg(game_->getRenderer(),"Press ENTER to add More Stars", game_->getFontMngr()->getFont(Resources::ARIAL24),{COLOR(0xff0000ff)});
		msg.render(game_->getWindowWidth()/2-msg.getWidth()/2,game_->getWindowHeight()-msg.getHeight()-10);
	}
};

