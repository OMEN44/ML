#include "FlappyBirdGame.h"

FlappyBirdGame::FlappyBirdGame(std::string title, int frameRateLimit)
	: Game(title, frameRateLimit),
	population(100)
{
}

void FlappyBirdGame::start()
{
}

void FlappyBirdGame::beforeUpdate()
{
	//gen walls
	if (this->wallGenBuffer == 175)
	{
		addObject(new Pipe(200 - this->level * 3));
		this->wallGenBuffer = 0;
		this->level++;
	}
	else
	{
		this->wallGenBuffer++;
	}

	//remove old pipes
	for (int i = 0; i < this->getGenericObjects().size(); i++)
		if (this->getObject(i)->getPosition().x <= -75)
			this->delObject(i);
	
	if (!this->population.allDead())
	{
		this->population.update(this->getGenericObjects());
	}
	else
	{
		this->population.reset();
	}
}

void FlappyBirdGame::onKeyPress(sf::Event& e)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		this->end();
	}
}

void FlappyBirdGame::beforeRender()
{
	this->population.render(this->window);
}
