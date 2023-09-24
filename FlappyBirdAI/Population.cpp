#include "Population.h"

Population::Population(int populationSize)
{
	for (int i = 0; i < populationSize; i++)
	{
		this->population.push_back(Bird());
	}
}

void Population::reset()
{
	for (auto& bird : this->population)
	{
		bird.crossOver(this->population);
		bird.reset();
	}
}

bool Population::allDead()
{
	for (Bird p : this->population)
	{
		if (!p.isDead())
			return false;
	}
	return true;
}

void Population::render(sf::RenderWindow& w)
{
	for (Bird& p : this->population)
	{
		// Update should handle AI stuff
		p.render(w);
	}
}

void Population::update(std::vector<RenderObject*> pipes)
{
	for (Bird& p : this->population)
	{
		p.update(pipes);
	}
}
