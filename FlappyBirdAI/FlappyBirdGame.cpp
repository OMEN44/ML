#include "FlappyBirdGame.h"

FlappyBirdGame::FlappyBirdGame(std::string title, int frameRateLimit)
	: Game(title, frameRateLimit)
{
}

void FlappyBirdGame::start()
{
	RenderObject *bird = new Player();
	addObject("player", bird);
	RenderObject* pipe = new Pipe(200);
	addObject(pipe);
}

void FlappyBirdGame::onInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		dynamic_cast<Player*>(this->getObject("player"))->flap();
}

void FlappyBirdGame::beforeUpdate()
{
	Player* bird = dynamic_cast<Player*>(this->getObject("player"));
	if (bird->getPosition().y > screenHeight - 50)
	{
		bird->setPosition(sf::Vector2f(100, screenHeight - 50));
		bird->velocity = -0.5;
	}

	if (this->wallCounter == 150)
	{
		addObject(new Pipe(200 - wallId * 3));
		this->wallCounter = 0;
		this->wallId++;
		if (this->getGenericObjects().size() > 20)
			this->getGenericObjects().erase(this->getGenericObjects().begin());
		this->score++;
		std::cout << this->score << std::endl;
	}
	else
	{
		this->wallCounter++;
	}

	//check collisions
	if (this->objectCollisionWithGeneric("player"))
		this->pause();
}

void FlappyBirdGame::onPause()
{
}

void FlappyBirdGame::pauseInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		this->end();
	}
}

void FlappyBirdGame::pauseUpdate()
{
}

void FlappyBirdGame::pauseRender()
{
}
