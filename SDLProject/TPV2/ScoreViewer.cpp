#include "ScoreViewer.h"

#include "Texture.h"
#include "Entity.h"
#include "SDL_macros.h"

ScoreViewer::ScoreViewer() :
		Component(ecs::ScoreViewer), //
		scoreManager_(nullptr) {
}

ScoreViewer::~ScoreViewer() {
}

void ScoreViewer::init() {
	scoreManager_ = GETCMP1_(ScoreManager);
}

//Renderiza el mensaje cuando ganas o pierdes
void ScoreViewer::draw() {

	Texture score(game_->getRenderer(),
			("SCORE: " + to_string(scoreManager_->getScore())),
			game_->getFontMngr()->getFont(Resources::ARIAL24),
			{ COLOR(0x111122ff) });

	score.render(game_->getWindowWidth() / 2 - score.getWidth() / 2, 10);

	if (scoreManager_->isGameOver()) {
		//Has ganado
		if (scoreManager_->isWin()) {
			Texture* gameOver = game_->getTextureMngr()->getTexture(
				Resources::Win);
			gameOver->render(game_->getWindowWidth() / 2 - gameOver->getWidth() / 2,
				game_->getWindowHeight() - gameOver->getHeight() - 150);
		}
		else//Has perdido
		{
			Texture* gameOver = game_->getTextureMngr()->getTexture(
				Resources::GameOver);
			gameOver->render(game_->getWindowWidth() / 2 - gameOver->getWidth() / 2,
				game_->getWindowHeight() - gameOver->getHeight() - 150);
		}

	}
}
