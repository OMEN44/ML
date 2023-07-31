#pragma once
#include <SFML/Graphics.hpp>
#include <map>

extern const unsigned short int SCREEN_WIDTH, SCREEN_HEIGHT;

class GameEngine
{
	std::map<std::string, sf::Drawable*> entities;
public:
	//Game operation
	void render(sf::RenderWindow& window);
	void input();
	void logic();

	//entity management
	void addEntity(std::string name, sf::Drawable* entity);
	void deleteEntity(std::string name);
	sf::Drawable* getEntity(std::string name);
};

