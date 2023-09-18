#pragma once
#include "Game.h"

class Player : public RenderObject
{
private:
	bool isAlive = false;
public:
	float velocity = 0;
	Player();
	void onCreate() override;
	void onUpdate(sf::Time deltaTime) override;

	void flap();
};