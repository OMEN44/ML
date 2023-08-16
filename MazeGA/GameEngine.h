#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>
#include <vector>
#include <random>
#include "Button.h"
#include "Slider.h"
#include "Dot.h"

extern float mutationRate, SCREEN_WIDTH, SCREEN_HEIGHT;
extern int selectionSize, pixelsPerStep, populationSize;
extern const float pi, steps;

class GameEngine
{
	//UI properties
	std::vector<sf::CircleShape*> walls;
	std::map<std::string, Button*> buttons;
	std::map<std::string, Slider*> sliders;
	sf::Color penColour = sf::Color::Green;
	sf::Vector2f* start = nullptr;
	sf::Vector2f* finish = nullptr;
	bool inBounds = false;
	bool drawing = false;
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
	void generatePopulation();
	bool generationDead();

	//Utils
	inline static float distance(sf::Vector2f a, sf::Vector2f b)
	{
		return static_cast<float>(sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)));
	}
};

