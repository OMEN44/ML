#include "Testing.h"
#include <iostream>

void Testing::test()
{
	std::for_each(
		this->entities.begin(),
		this->entities.end(),
		[&](std::pair<std::string, sf::Drawable*> keyValue) {
			if (keyValue.first == "first")
				this->deleteEntity(keyValue.first);
		}
	);
}


sf::Drawable* Testing::getEntity(std::string name)
{
	auto it = this->entities.find(name);
	return (it != this->entities.end()) ? it->second : nullptr;
}

void Testing::deleteEntity(std::string name)
{
	auto it = this->entities.find(name);
	if (it != this->entities.end())
	{
		this->entities.erase(it);
	}
}

void Testing::addEntity(std::string name, sf::Drawable* entity)
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
