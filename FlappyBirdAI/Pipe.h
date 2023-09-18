#pragma once
#include <random>
#include <ctime>

#include "Game.h"

class Pipe : public RenderObject
{
private:
	int gapSize;
public:
	Pipe(int gapSize);
	void onCreate() override;
	void onUpdate(sf::Time deltaTime) override;
};

