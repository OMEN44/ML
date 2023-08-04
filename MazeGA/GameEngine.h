#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include "Button.h"

extern unsigned short int SCREEN_WIDTH, SCREEN_HEIGHT;

class GameEngine
{
	std::map<std::string, sf::Drawable*> entities;
	std::map<std::string, Button*> buttons;
	sf::Color penColour = sf::Color::Blue;
	bool inBounds = false;
	bool drawing = false;
	bool showControllPanel = true;
	int dotIndex = 0;
	int brushSize = 10;
public:
	GameEngine();
	~GameEngine();

	//Game operation
	void renderAll(sf::RenderWindow& window);
	void renderDynamicObjects(sf::RenderWindow& window);
	void renderStaticObjects(sf::RenderWindow& window);
	void input(sf::Event& e, sf::RenderWindow& window);
	void logic();

	//entity management
	void addEntity(std::string name, sf::Drawable* entity);
	void deleteEntity(std::string name);
	sf::Drawable* getEntity(std::string name);

	//Utils
	inline static float distance(sf::Vector2f a, sf::Vector2f b)
	{
		return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
	}
};

