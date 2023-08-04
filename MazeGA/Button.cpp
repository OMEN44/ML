#include "Button.h"

Button::Button(float x, float y, float width, float height, sf::Color colour, std::string textureFile)
{
	this->position = sf::Vector2f(x, y);
	this->size = sf::Vector2f(width, height);
	this->r = colour.r;
	this->g = colour.g;
	this->b = colour.b;
	this->a = colour.a;
	this->texture = new sf::Texture();
	this->texture->loadFromFile(textureFile);
}

Button::Button(float x, float y, float width, float height, sf::Color colour, sf::Texture texture)
{
	this->position = sf::Vector2f(x, y);
	this->size = sf::Vector2f(width, height);
	this->r = colour.r;
	this->g = colour.g;
	this->b = colour.b;
	this->a = colour.a;
	this->texture = &texture;
}

inline void Button::setTexture(sf::Texture* texture)
{
	this->texture = texture;
}

inline void Button::toggleEnabled()
{
	this->enabled = !this->enabled;
}

void Button::setPosition(sf::Vector2f position)
{
	this->position = position;
}

inline bool Button::isEnabled()
{
	return this->enabled;
}

sf::RectangleShape Button::getDrawable()
{
	sf::RectangleShape r(this->size);
	sf::Color c(this->r, this->g, this->b, this->a);
	r.setFillColor(c);
	r.setPosition(this->position);
	r.setTexture(this->texture);

	return r;
}