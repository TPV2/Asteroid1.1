#include "GameCtrl.h"
#include "Entity.h"
#include "InputHandler.h"
#include "SDL_macros.h"
#include "GameLogic.h"

GameCtrl::~GameCtrl() {
}

void GameCtrl::init() {
	scoreManager_ = GETCMP1_(ScoreManager);
}

//Comprueba el estado del juego 
void GameCtrl::update() {
	//Genera los asteroides y cambia el estado del juego para que empiece
	if (!scoreManager_->isGameOver() && !scoreManager_->isRunning()) {
		if (InputHandler::instance()->keyDownEvent()) {
			astPool_->generateAsteroids(ASTEROIDS_NUM);
			scoreManager_->setRunning(true);
			game_->getAudioMngr()->playMusic(Resources::March, -1);
		}
	}
	//Cuando el jugador se queda sin vidas
	if (health_->getLives() < 0) {
		GETCMP1_(GameLogic)->resetFighter();
		scoreManager_->setRunning(false);
		scoreManager_->setGameOver(true);
	}
	//Cuando el jugador ha ganado
	if (scoreManager_->isRunning() && astPool_->getNumOfAsteroids() == 0) {
		GETCMP1_(GameLogic)->resetFighter();
		scoreManager_->setRunning(false);
		scoreManager_->setGameOver(true);
		scoreManager_->setWin(true);
	}
	//Después de que el jugador haya ganado o perdido, reinicia la escena ( puntos, vidas y música)
	if (scoreManager_->isGameOver() && InputHandler::instance()->keyDownEvent()) {
		GETCMP1_(GameLogic)->resetFighter();
		scoreManager_->resetScore();
		health_->resetLives();
		game_->getAudioMngr()->pauseMusic();
		scoreManager_->setGameOver(false);
	}
}

//Renderiza el mensaje de press any key
void GameCtrl::draw() {

	if (!scoreManager_->isRunning() && !scoreManager_->isGameOver()) {
		Texture *hitanykey = game_->getTextureMngr()->getTexture(
				Resources::PressAnyKey);
		hitanykey->render(
				game_->getWindowWidth() / 2 - hitanykey->getWidth() / 2,
				game_->getWindowHeight() - hitanykey->getHeight() - 50);
	}
}

