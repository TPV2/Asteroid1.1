#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "Resources.h"
#include "SDLGame.h"

#pragma region constantes
const double BULLET_W = 4;
const double BULLET_H = 4;
const double BULLET_VEL = 3;
#pragma endregion


struct Bullet
{
private:
	Vector2D pos_;
	Vector2D scale_;
	double vel_;
	Vector2D dir_;
	double angle_;
	bool used_ = false;
public:
	Bullet(Vector2D pos, Vector2D scale, double angle) :
		pos_(pos), scale_(scale), vel_(BULLET_VEL), angle_(angle) {}
	Bullet() :
		pos_({ 0.0,0.0 }), scale_({ BULLET_W,BULLET_H }), vel_(BULLET_VEL), angle_(0) {};
	//Para saber si un objeto está en uso
	bool isUsed() { return used_; };
	//Para cambiar el estado de un objeto de usado a no usado y viceversa
	void setObject(bool status) { used_ = status; };
	void startBullet(Vector2D pos, Vector2D dir) {
		vel_ = BULLET_VEL;
		pos_ = pos;
		dir_ = dir;
		used_ = true;
	}


#pragma region getters
	const Vector2D* getPos() { return &pos_; };
	const double getVel() { return vel_; };
	const Vector2D* getScale() { return &scale_; };
	const double getAngle() { return angle_; };
	const Vector2D* getDir() { return &dir_; };

#pragma endregion
#pragma region setters
	void setPos(Vector2D pos) { pos_ = pos; };
	void setVel(double vel) { vel_ = vel; };
	void setScale(Vector2D scale) { scale_ = scale; };
	void setAngle(double angle) { angle_ = angle; };
	void setDir(Vector2D dir) { dir_ = dir; };
#pragma endregion

};




