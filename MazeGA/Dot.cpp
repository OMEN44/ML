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

void Dot::takeStep(sf::Vector2f* goal, std::vector<sf::CircleShape*> walls, int numberOfSteps)
{
	if (!this->isAlive(goal, walls)) return;
	if (numberOfSteps + this->step > steps)
	{
		std::cout << "died" << std::endl;
		this->alive = false;
	}
	else 
	{
		this->position = sf::Vector2f(
			this->position.x + pixelsPerStep * cos(this->moves[this->step] * (pi / 180)),
			this->position.y + pixelsPerStep * sin(this->moves[this->step] * (pi / 180))
		);
		this->step += numberOfSteps;
	}
}

void Dot::mutate()
{
	for (int i = 0; i < steps; i++)
		this->moves[i] *= Dot::randF(1 - (mutationRate / 100), 1 + (mutationRate / 100));
}

bool Dot::isAlive()
{
	return this->alive;
}

bool Dot::isAlive(sf::Vector2f* goal, std::vector<sf::CircleShape*> walls)
{
	if (goal != nullptr && (GameEngine::distance(sf::Vector2f(5, 5) + *goal, this->getPosition()) <= 10
		|| this->step == steps
		|| this->position.x <= 10
		|| this->position.x >= SCREEN_WIDTH - 10
		|| this->position.y <= 10
		|| this->position.y >= SCREEN_HEIGHT - 10))
		this->alive = false;
	std::for_each(
		walls.begin(),
		walls.end(),
		[this](sf::CircleShape* wall)
		{
			if (GameEngine::distance(
				sf::Vector2f(wall->getRadius(), wall->getRadius()) + wall->getPosition(),
				sf::Vector2f(5, 5) + this->getPosition()
			) <= wall->getRadius())
			{
				this->alive = false;
			}
		}
	);

	
	return this->alive;
}

float Dot::getFitness(sf::Vector2f* goal) 
{
	if (goal != nullptr)
		this->fitness = abs(1.0 / GameEngine::distance(*goal, this->position) * (step / steps));
	return this->fitness;
}

float Dot::getStep(int stepIndex)
{
	return this->moves[stepIndex];
}