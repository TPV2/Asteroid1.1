#pragma once
#include "System.h"
#include "Entity.h"
#include "Manager.h"
#include "Transform.h"
#include "AsteroidPool.h"
#include <SDL_stdinc.h> // for Uint32
#include "SDLGame.h" //Para audio manager
#include "SDL_macros.h"
#include <stdlib.h>


class AsteroidsSystem :
	public System
{
public:
	AsteroidsSystem() :
		System(ecs::_sys_Asteroids) {}

	//Gestiona la colisión de un asteroide cuando colisiona contra el fighter
	void onCollision(Entity* e) {
		Transform* tr = e->getComponent<Transform>(ecs::Transform);
		e->setActive(false);
		tr->position_.set({ -500,-500 });
		tr->velocity_.set({ 0,0 });
		tr->rotation_ = 0;
		tr->height_ = 0;
		tr->width_ = 0;
	}

	//Divide un asteroide si tiene nivel 1 o más
	void onCollisionWithBullet(Entity* a) {
		//Sonido de explosión
		game_->getAudioMngr()->playChannel(Resources::AudioId::Explosion, 0, (int)EFFECTS::AstExp);
		game_->getAudioMngr()->setChannelVolume(5, (int)EFFECTS::AstExp);
		auto astLifeTime = a->getComponent<AsteroidLifeTime>(ecs::AsteroidLifeTime);
		//cout << "Has golpeado un asteroide de nivel: " << astLifeTime->getAstLevel() << endl;
		astLifeTime->removeLevel();
		if (astLifeTime->getAstLevel() >= 1) {
			//el asteroide original
			Transform* origialAst = a->getComponent<Transform>(ecs::Transform);

			//Primer asteroide
			int ast1Lvl = astLifeTime->getAstLevel();
			Vector2D ast1Pos = origialAst->position_;
			Vector2D ast1Scale = { ASTEROID_W + ASTEROID_DIFERENCE * ast1Lvl, ASTEROID_H + ASTEROID_DIFERENCE * ast1Lvl };
			Vector2D ast1Vel = generarSpeed();
			double ast1Rot = origialAst->rotation_;
			Uint32 ast1CurrLifeTime = game_->getTime();
			Entity* ast1 = mngr_->addEntity<AsteroidPool>(ast1Pos, ast1Scale, ast1Vel, ast1Rot, ast1Lvl, ast1CurrLifeTime);
			if (ast1 != nullptr) {
				ast1->setActive(true);
				ast1->addToGroup(ecs::_grp_Asteroid);
			}

			//Segundo asteroide
			int ast2Lvl = astLifeTime->getAstLevel();
			Vector2D ast2Pos = origialAst->position_;
			Vector2D ast2Scale = { ASTEROID_W + ASTEROID_DIFERENCE * ast2Lvl, ASTEROID_H + ASTEROID_DIFERENCE * ast2Lvl };
			Vector2D ast2Vel = generarSpeed();
			double ast2Rot = origialAst->rotation_;
			Uint32 ast2CurrLifeTime = game_->getTime();
			Entity* ast2 = mngr_->addEntity<AsteroidPool>(ast2Pos, ast2Scale, ast2Vel, ast2Rot, ast2Lvl, ast2CurrLifeTime);
			if (ast2 != nullptr) {
				ast2->setActive(true);
				ast2->addToGroup(ecs::_grp_Asteroid);
			}
		}
		a->setActive(false);
	}

	//Crea asteroides en posiciones aleatorias y los mete al grupo de asteroides al inicio del juego
	void addAsteroids(std::size_t n) {
		for (auto i(0u); i < n; i++) {
			int rotation = game_->getRandGen()->nextInt(1, 2);
			int level = game_->getRandGen()->nextInt(0, MAX_LEVEL) + 1;	//Asteroides nivel 3 - 2 - 1 (0 es cuando se destuye)
			Vector2D pos;
			double width = ASTEROID_W + ASTEROID_DIFERENCE * level, height = ASTEROID_H + ASTEROID_DIFERENCE * level;
			SDL_Rect fighterBox;
			do{
				pos = { (double)game_->getRandGen()->nextInt(0 , game_->getWindowWidth()),
					(double)game_->getRandGen()->nextInt(0, game_->getWindowHeight()) };
				fighterBox = RECT(pos.getX(), pos.getY(), width, height);
			}
			while (checkPlayerPos(&fighterBox));

			Vector2D speed = generarSpeed();

			Uint32 lt = game_->getRandGen()->nextInt(MIN_LIFE_TIME, MAX_LIFE_TIME);

			Entity* e = mngr_->addEntity<AsteroidPool>(pos, Vector2D{ width,height }, speed, rotation, level, lt);
			if (e != nullptr)
				e->addToGroup(ecs::_grp_Asteroid);
		}
	}

	//Cambia las velocidades entre dos asteroides
	void onCollisionAsteroid(Entity* ast1,Vector2D otherVel) {
		auto ast1Tr = ast1->getComponent<Transform>(ecs::Transform);
		ast1Tr->velocity_.setX(otherVel.getX() * -1);
		ast1Tr->velocity_.setY(otherVel.getY() * -1);
		ast1Tr->rotation_++;
	}

	//Movimiento de los asteroides
	void update()override;

	//comprueba si un asteroide se está creando sobre el figther 
	bool checkPlayerPos(SDL_Rect* currAst) {
		auto fighterTr = mngr_->getHandler(ecs::_hdlr_Fighter)->getComponent<Transform>(ecs::Transform);
		SDL_Rect fighterBox = RECT((int)fighterTr->position_.getX(), (int)fighterTr->position_.getY(), 
			(int)fighterTr->width_ + 250, (int)fighterTr->height_ + 250);
		if (SDL_HasIntersection(currAst, &fighterBox)) {
			return true;
		}
		else
		{
			return false;
		}
	}

	//Devuelve la cantidad de asteroides activos en el juego
	const int getAsteroidsActive() { return asteroidsActive; };
	
	//Genera una velocidad aleatoria para los meteoritos
	Vector2D generarSpeed() {
		Vector2D speed{ 0,0 };
		//Para evitar meteoritos con velocidades muy pequeñas (parados)
		while (abs(speed.getX()) < 1.5 && abs(speed.getY()) < 1.5) {
			speed.setX(game_->getRandGen()->nextInt(MIN_SPEED * 10, MAX_SPEED * 10) / 10.0);	//Para que el double 2.6 pase a se 26 y se calcule bien el int aleatorio
			speed.setY(game_->getRandGen()->nextInt(MIN_SPEED * 10, MAX_SPEED * 10) / 10.0);
		}
		//cout << "SPEED: {" << speed.getX() << ", " << speed.getY() << "}" << endl;
		return speed;
	}
private:
	//Cantidad de asteroides activos
	int asteroidsActive = 0;

	const int MAX_LEVEL = 3;
	const double MIN_SPEED = -2.6;
	const double MAX_SPEED = 2.6;
	const double MIN_SCALE = 30;
	const double MAX_SCALE = 50;
	//En segundos
	const int MIN_LIFE_TIME = 5;
	const int MAX_LIFE_TIME = 10;
	//Asteroides
	const double ASTEROID_W = 16;
	const double ASTEROID_H = 16;
	const double ASTEROID_DIFERENCE = 12;

};

