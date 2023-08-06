#pragma once
#include <vector>
#include <iostream>
#include "SFML/Graphics.hpp"

class Dot
{
	sf::Vector2f position;
	std::vector<float> moves;
	bool alive = true;
	int step = 0;
	float fitness = -1;
public:
	Dot();
	Dot(sf::Vector2f startingPosition);
	Dot(sf::Vector2f startingPostition, std::vector<float> moves);

	sf::Vector2f getPosition();
	void takeStep(sf::CircleShape* goal, int numberOfSteps = 1);
	void mutate();
	bool isAlive(sf::CircleShape* goal);
	float getFitness(sf::CircleShape* goal);
	float getStep(int stepIndex);

	//static methods
	inline static float randF(float min, float max) {
		return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
	}

	inline static float randF(float max) {
		return static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / max));
	}

	inline static int randI(int min, int max) {
		return static_cast<int>(rand()) / (static_cast<int>(RAND_MAX / (max - min)));
	}

	inline static int randI(int max) {
		return static_cast<int>(rand()) / (static_cast<int>(RAND_MAX / max));
	}
};

