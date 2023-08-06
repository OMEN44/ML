#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>
#include <vector>
#include <random>
#include "Button.h"
#include "Dot.h"

extern float SCREEN_WIDTH, SCREEN_HEIGHT;
extern const int selectionSize, pixelsPerStep, populationSize, steps;
extern const float mutationRate, pi;

class GameEngine
{
	//UI properties
	std::map<std::string, sf::Drawable*> entities;
	std::map<std::string, Button*> buttons;
	sf::Color penColour = sf::Color::Blue;
	sf::CircleShape* start = nullptr;
	sf::CircleShape* finish = nullptr;
	bool inBounds = false;
	bool drawing = false;
	bool showControllPanel = true;
	int dotIndex = 0;
	int brushSize = 10;
	//Genetic algorithm
	std::vector<Dot> population;
	bool simulating = false;
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
	void generatePopulation();
	bool generationDead();

	//Utils
	inline static float distance(sf::Vector2f a, sf::Vector2f b)
	{
		return static_cast<float>(sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)));
	}
};

