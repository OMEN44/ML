#pragma once
#include <vector>

#include "Bird.h"
#include "Pipe.h"

class Population
{
private:
	std::vector<Bird> population;
public:
	Population(int populationSize);
	void reset();
	bool allDead();
	void update(std::vector<RenderObject*> pipes);
	void render(sf::RenderWindow& w);
};

