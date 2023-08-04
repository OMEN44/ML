#pragma once
#include <SFML/Graphics.hpp>

class Button
{
	sf::Vector2f position, size;
	int r, g, b, a;
	bool enabled = true;
	sf::Texture* texture;
	

public:
	Button(float x, float y, float width, float height, sf::Color colour, std::string textureFile);
	Button(float x, float y, float width, float height, sf::Color colour, sf::Texture texture);
	void setPosition(sf::Vector2f position);
	inline void setTexture(sf::Texture* texture);
	inline void toggleEnabled();
	inline bool isEnabled();
	sf::RectangleShape getDrawable();
};

