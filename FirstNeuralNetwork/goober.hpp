#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
class Goober
{
	sf::Vector2f position;
	float bodyRadius = 10;
	float direction = 0;
public:
	Goober(sf::Vector2f position);
	void draw(sf::RenderWindow& window);
	void logic(float dt);
	void setPosition(sf::Vector2f position);
	void forward(float distance);
	void rotate(float angle);
};

