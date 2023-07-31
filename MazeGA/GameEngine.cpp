#include "GameEngine.h"
#include <iostream>
const unsigned short int SCREEN_WIDTH = 600;
const unsigned short int SCREEN_HEIGHT = 400;

void GameEngine::render(sf::RenderWindow& window)
{
	std::map<std::string, sf::Drawable*>::iterator it = this->entities.begin();


	while (it != this->entities.end())
	{
		window.draw(*(it->second));
		++it;
	}
	
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
		this->entities.insert(std::pair<std::string, sf::Drawable*>(name, entity));
	} 
	else
	{
		std::cout << "Didn't add entity: " << name << " Becuase it already exists." << std::endl;
	}
}

void GameEngine::deleteEntity(std::string name)
{
	if (this->entities.count(name))
	{
		this->entities.erase(name);
	}
	else
	{
		std::cout << "Nothing was removed becuase there was no entity labeled: " << name << std::endl;
	}
}

sf::Drawable* GameEngine::getEntity(std::string name)
{
	return this->entities[name];
}