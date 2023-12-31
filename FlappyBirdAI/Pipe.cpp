#include "Pipe.h"

Pipe::Pipe(int gapSize) : RenderObject(sf::Vector2f(0, 0)), gapSize(gapSize) {  }

void Pipe::onCreate()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distribution(0, screenHeight - this->gapSize);
	int height = distribution(gen);
		
	this->setPosition(sf::Vector2f(screenWidth, height));
	sf::RectangleShape rec(sf::Vector2f(75, 1000));
	rec.setFillColor(sf::Color::Green);
	rec.setPosition(0, -1000);
	this->addBodyMember(new sf::RectangleShape(rec));
	rec.setPosition(0, this->gapSize);
	this->addBodyMember(new sf::RectangleShape(rec));
}

void Pipe::onUpdate(sf::Time deltaTime)
{
	this->move(sf::Vector2f(-2, 0));
}

int Pipe::getGapSize()
{
	return this->gapSize;
}