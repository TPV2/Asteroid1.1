#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "Resources.h"
#include "SDLGame.h"

#pragma region constantes
const double ASTEROID_W = 16;
const double ASTEROID_H = 16;
const double ASTEROID_DIFERENCE = 8;
const double ASTEROID_MAX_VEL = 2.6;
const double ASTEROID_MIN_VEL = 1.2;
const double ASTEROID_MIN_ROT = -1.5;
const double ASTEROID_MAX_ROT = 1.5;
#pragma endregion

struct Asteroid
{
private:
	Vector2D pos_;	
	Vector2D dir_;
	double w_ = ASTEROID_W;		//Son constantes
	double h_ = ASTEROID_H;		
	double vel_;	
	double angle_;	
	int level_ = 1;		// 1-3 (pequeño-grande), 0 es destruido
	bool used_ = false;
	int points_ = 10;
	double angleSpeed_ = 0;

public:
	Asteroid(Vector2D pos, Vector2D dir, double vel, double angle, int level) :
		pos_(pos), dir_(dir), vel_(vel), angle_(angle), level_(level) {}
	Asteroid() :
		pos_({ 0.0,0.0 }), dir_({ 0, 0 }), vel_(0), angle_(0), level_(0) {};
	//Para saber si un objeto está en uso
	bool isUsed() { return used_; };
	//Para cambiar un objeto de usado a no usado
	void setObject(bool status) { used_ = status; };
	void startAsteroid(Vector2D pos, Vector2D dir, double vel, double angle, double level,double angleSpeed) {
		pos_ = pos;
		dir_ = dir;
		vel_ = vel;
		angle_ = angle;
		level_ = level;
		w_ = ASTEROID_W + ASTEROID_DIFERENCE * level;
		h_ = ASTEROID_H + ASTEROID_DIFERENCE * level;
		angleSpeed_ = angleSpeed;
		used_ = true;
	}

#pragma region getters
	const Vector2D* getPos() { return &pos_; };
	const Vector2D* getDir() { return &dir_; };
	const double getVel() { return vel_; };
	const double getW() { return w_; };
	const double getH() { return h_; };
	const double getAngle() { return angle_; };
	const int getLevel() { return level_; };
	const int getPoints() { return points_; };
	const double getAngleSpeed() { return angleSpeed_; };
#pragma endregion
#pragma region setters
	void setAngleSpeed(double value) { angleSpeed_ = value; };
	void setPoints(int value) { points_ = value; };
	void setPos(Vector2D pos) { pos_ = pos; };
	void setDir(Vector2D dir) { dir_ = dir; };
	void setVel(double vel) { vel_ = vel; };
	void setW(double w) { w_ = w; };
	void setH(double h) { h_ = h; };
	void setAngle(double angle) { angle_ = angle; };
	void setLevel(int level) { level_ = level; };
#pragma endregion

};

