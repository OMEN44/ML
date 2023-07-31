#include "GameEngine.h"
#include <iostream>
const unsigned short int SCREEN_WIDTH = 600;
const unsigned short int SCREEN_HEIGHT = 400;

GameEngine::GameEngine() {}

GameEngine::~GameEngine() {
	
}

void GameEngine::render(sf::RenderWindow& window)
{
	std::for_each(
		this->entities.begin(),
		this->entities.end(),
		[&](std::pair<std::string, sf::Drawable*> keyValue) {
			window.draw(*(this->getEntity(keyValue.first)));
		}
	);
}

void GameEngine::input()
{

}

void GameEngine::logic()
{

}

void GameEngine::addEntity(std::string name, sf::Drawable* entity)
{
	if (!this->entities.count(name)) 
	{
		this->entities[name] = entity;
	} 
	else
	{
		std::cout << "Didn't add entity: " << name << " Becuase it already exists." << std::endl;
	}
}

void GameEngine::deleteEntity(std::string name)
{
	auto it = this->entities.find(name);
	if (it != this->entities.end())
	{
		delete it->second;
		this->entities.erase(it);
	}
}

sf::Drawable* GameEngine::getEntity(std::string name)
{
	auto it = this->entities.find(name);
	return (it != this->entities.end()) ? it->second : nullptr;
}