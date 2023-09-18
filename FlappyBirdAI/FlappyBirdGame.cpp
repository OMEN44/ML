#include "FlappyBirdGame.h"

FlappyBirdGame::FlappyBirdGame(std::string title, int frameRateLimit)
	: Game(title, frameRateLimit)
{
}

void FlappyBirdGame::start()
{
	RenderObject *bird = new Player();
	addObject("player", bird);
	RenderObject *pipe = new Pipe(200);
	addObject(pipe);
}

void FlappyBirdGame::beforeUpdate()
{
	Player* bird = dynamic_cast<Player*>(this->getObject("player"));
	if (bird->getPosition().y > screenHeight - 50)
	{
		bird->setPosition(sf::Vector2f(100, screenHeight - 50));
		bird->velocity = -0.5;
	}

	if (this->wallCounter == 175)
	{
		addObject(new Pipe(200 - wallId * 3));
		this->wallCounter = 0;
		this->wallId++;
		if (this->getGenericObjects().size() > 5)
			this->delObject(0);
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

void FlappyBirdGame::onKeyPress(sf::Event& e)
{
	if (e.key.code == sf::Keyboard::Space && !this->flapping)
	{
		dynamic_cast<Player*>(this->getObject("player"))->flap();
		this->flapping = true;
	}
}

void FlappyBirdGame::onKeyRelease(sf::Event& e)
{
	this->flapping = !(e.key.code == sf::Keyboard::Space);
}

void FlappyBirdGame::pauseInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		this->end();
	}
}
