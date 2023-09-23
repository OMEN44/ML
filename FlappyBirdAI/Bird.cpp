#include "Bird.h"

Bird::Bird()
{
	this->topology = { 2, 1 };
	this->reset();
	this->genRandomNetwork();
}

bool Bird::isDead()
{
	return this->dead;
}

sf::Vector2f Bird::getPosition()
{
	return this->position;
}

void Bird::setPosition(sf::Vector2f position)
{
	this->position = position;
}

void Bird::reset()
{
	this->dead = false;
	this->position = sf::Vector2f(100, 400);
	this->fitness = 0;
	this->velocity = 0;
}

unsigned Bird::getFitness()
{
	return this->fitness;
}

sf::Vector2f Bird::getPipeDistance(std::vector<RenderObject*> pipes)
{
	for (auto* pipe : pipes)
	{
		//if pipe infront of bird
		if (pipe->getPosition().x > 100)
		{
			return sf::Vector2f(pipe->getPosition().x - 100, this->position.y - pipe->getPosition().y);
		}
	}
	//should never reach here unless there is no pipes exisiting
	return sf::Vector2f(0, 0);
}

void Bird::render(sf::RenderWindow& w)
{
	sf::CircleShape c(10);
	c.setFillColor(sf::Color::Yellow);
	c.setPosition(this->position + sf::Vector2f(10, 10));
	w.draw(c);
}

void Bird::update(std::vector<RenderObject*> pipes)
{
	//check for death
	for (auto* pipe : pipes)
	{
		if (this->position.x > pipe->getPosition().x - 30 && this->position.x < pipe->getPosition().x + 60)
		{
			if (this->position.y < pipe->getPosition().y || this->position.y > pipe->getPosition().y - 20 + dynamic_cast<Pipe*>(pipe)->getGapSize())
			{
				this->dead = true;
			}
		}
	}

	if (this->dead)
	{
		this->position += sf::Vector2f(-2, 0);
	}
	else
	{
		this->velocity += 0.5;
		this->position += sf::Vector2f(0, this->velocity);
		if (this->feedForward(pipes))
			this->velocity = -10;
	}
}

void Bird::crossOver()
{

}

bool Bird::feedForward(std::vector<RenderObject*> pipes)
{
	if (this->position.y > rand() % 300 + 300)
		return true;
	return false;
}

void Bird::genRandomNetwork()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> distribution(-1, 1);

	this->neuronBias.push_back(std::vector<float>());
	this->weights.push_back(std::vector<std::vector<float>>());

	for (int layer = 1; layer < this->topology.size(); layer++)
	{
		this->neuronBias.push_back(std::vector<float>());
		this->weights.push_back(std::vector<std::vector<float>>());
		for (int size = 0; size < this->topology[layer]; size++)
		{
			this->neuronBias[layer].push_back(distribution(gen));
			this->weights[layer].push_back(std::vector<float>());
			for (int connection = 0; connection < this->topology[layer - 1]; connection++)
			{
				this->weights[layer][size].push_back(distribution(gen));
			}
		}
	}
}
