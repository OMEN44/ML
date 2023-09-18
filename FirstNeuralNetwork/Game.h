#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <map>

#include "goober.hpp"
#include "NeuralNetwork.h"

using std::cout;
using std::endl;

extern unsigned screenHeight, screenWidth;

class Game
{
	std::vector<Goober> generation;
	std::map<std::string, sf::Drawable*> objects;
	NeuralNetwork* n;
public:
	Game();
	~Game();

	void addObject(std::string name, sf::Drawable* object);
	void delObject(std::string name);
	sf::Drawable* getObject(std::string name);

	void update(float dt);
	void render(sf::RenderWindow& w);
	void input(sf::RenderWindow& w, sf::Event& e);
};

