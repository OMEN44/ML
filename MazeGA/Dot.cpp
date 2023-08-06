#include "Dot.h"
#include "GameEngine.h"

Dot::Dot() {}

Dot::Dot(sf::Vector2f start)
{
	this->position = sf::Vector2f(start);
	for (int i = 0; i < steps; i++)
		this->moves.push_back(Dot::randF(360));
}

Dot::Dot(sf::Vector2f start, std::vector<float> moves)
{
	this->position = sf::Vector2f(start);
	this->moves = moves;
}

sf::Vector2f Dot::getPosition()
{
	return this->position;
}

void Dot::takeStep(sf::CircleShape* goal, int numberOfSteps)
{
	if (!this->isAlive(goal)) return;
	if (numberOfSteps + this->step >= steps)
		this->alive = false;
	else 
	{
		this->step += numberOfSteps;
		this->position = sf::Vector2f(
			this->position.x + pixelsPerStep * cos(this->moves[this->step] * (pi / 180)),
			this->position.y + pixelsPerStep * sin(this->moves[this->step] * (pi / 180))
		);
	}
}

void Dot::mutate()
{
	for (int i = 0; i < steps; i++)
		this->moves[i] *= Dot::randF(1 - (mutationRate / 100), 1 + (mutationRate / 100));
}

bool Dot::isAlive(sf::CircleShape* goal)
{
	if (sqrt(pow(goal->getPosition().x - this->getPosition().x, 2) + pow(goal->getPosition().x - this->getPosition().x, 2)) <= goal->getRadius()
		|| this->step == steps
		|| this->position.x <= 10
		|| this->position.x >= SCREEN_WIDTH - 10
		|| this->position.y <= 10
		|| this->position.y >= SCREEN_HEIGHT - 10)
		this->alive = true;
	//check for collisons with wall.
	std::cout << "alive!!" << step << std::endl;
	return this->alive;
}

float Dot::getFitness(sf::CircleShape* goal) 
{
	this->fitness = abs(1.0 / sqrt(pow(goal->getPosition().x - this->getPosition().x, 2) + pow(goal->getPosition().x - this->getPosition().x, 2)));
	return this->fitness;
}

float Dot::getStep(int stepIndex)
{
	return this->moves[stepIndex];
}