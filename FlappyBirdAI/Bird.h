#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

#include "Game.h"
#include "Pipe.h"

class Bird
{
private:
	sf::Vector2f position;
	std::vector<std::vector<std::vector<float>>> weights;
	std::vector<std::vector<float>> neuronBias;
	std::vector<unsigned short> topology;
	float velocity;
	unsigned fitness;
	bool dead;
public:
	Bird();

	//getters and setters
	bool isDead();
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f position);
	void reset();
	unsigned getFitness();
	sf::Vector2f getPipeDistance(std::vector<RenderObject*> pipes);

	//game functions
	void render(sf::RenderWindow& w);
	void update(std::vector<RenderObject*> pipes);

	//ai functions
	void crossOver();
	bool feedForward(std::vector<RenderObject*> pipes);
	void genRandomNetwork();
};

