#pragma once
#include <SFML/Graphics.hpp>
class Slider
{
	float buttonX, min, max, width, height;
	sf::Vector2f position;
	std::string label;
	bool moving = false;
	sf::RectangleShape button;
public:
	Slider(sf::Vector2f position, std::string label, float min, float max);
	float getValue();
	float getPercent();
	void setSize(float width, float height);
	void setPosition(sf::Vector2f position);
	void setValue(float value);
	void setPercentage(float value);
	void draw(sf::RenderWindow& window);
	void logic(sf::RenderWindow& window);
	sf::Vector2f getPosition();
};

