#pragma once

#include "Component.h"

class ScoreManager: public Component {
private:
	bool running_;
	bool win_;
	bool gameOver_;
	int score_;

public:
	ScoreManager() : Component(ecs::ScoreManager),win_(false), running_(false), score_(0),gameOver_(false) {}
	~ScoreManager() {};
	
#pragma region getters
	const int getScore() { return score_; };
	bool isRunning() const { return running_; };
	bool isGameOver() const { return gameOver_; };
	bool isWin() const { return win_; };
#pragma endregion
#pragma region setters
	void setWin(bool win) { win_ = win; };
	void addScore(int value) { score_ += value; };
	void resetScore() { score_ = 0; win_ = false; };
	void setRunning(bool running) { running_ = running; };
	void setGameOver(bool status) { gameOver_ = status; };
#pragma endregion
};
