#pragma once
#include <map>
#include <SFML/Graphics.hpp>

class Testing
{
	std::map<std::string, sf::Drawable*> entities;
public:
	void test();
	void addEntity(std::string name, sf::Drawable* entity);
	void deleteEntity(std::string name);
	sf::Drawable* getEntity(std::string name);
};

