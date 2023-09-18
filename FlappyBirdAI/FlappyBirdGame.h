#pragma once
#include "Game.h"
#include "Player.h"
#include "Pipe.h"

class FlappyBirdGame : public Game
{
private:
	int wallCounter = 0;
	int wallId = 1;
	int score = 0;
public:
	FlappyBirdGame(std::string title, int frameRateLimit);
	void start() override;
	void onInput() override;
	void beforeUpdate() override;

	void onPause() override;
	void pauseInput() override;
	void pauseUpdate() override;
	void pauseRender() override;
};

