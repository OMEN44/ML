#pragma once
#include "Game.h"
#include "Bird.h"
#include "Pipe.h"
#include "Population.h"

class FlappyBirdGame : public Game
{
private:
	int wallGenBuffer = 0;
	int level = 0;
	Population population;
public:
	FlappyBirdGame(std::string title, int frameRateLimit);
	void start() override;
	void beforeUpdate() override;
	void onKeyPress(sf::Event& e) override;
	void beforeRender() override;
};

