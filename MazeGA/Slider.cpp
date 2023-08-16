#include "Slider.h"
Slider::Slider(sf::Vector2f position, std::string label, float min, float max)
{
	this->position = position;
	this->label = label;
	this->min = min;
	this->max = max;
	this->buttonX = this->position.x;
	this->width = 120;
	this->height = 20;
	this->button = sf::RectangleShape(sf::Vector2f(this->width / 5, this->height));
}

float Slider::getValue()
{
	return ((this->buttonX - this->position.x) / this->width) * (this->max - this->min) + this->min;
}

float Slider::getPercent()
{
	return (this->getValue() - this->min) / (this->max - this->min);
}

void Slider::setSize(float width, float height)
{
	this->width = width;
	this->height = height;
}

void Slider::setPosition(sf::Vector2f position)
{
	this->position = position;
}

void Slider::setValue(float value)
{
	this->buttonX = (value - this->min) / (this->max - this->min) * this->width + this->position.x;
}

void Slider::setPercentage(float value)
{
	this->buttonX = value * this->width + this->position.x;
}

void Slider::draw(sf::RenderWindow& window)
{
	sf::Font f;
	f.loadFromFile("C:\\Users\\huons\\OneDrive\\Documents\\programming\\Resources\\Arial.ttf");
	sf::Text text(this->label + ": " + std::to_string(static_cast<int>(this->getValue())), f, 15);
	text.setPosition(sf::Vector2f(this->position.x, this->position.y - 18));

	sf::RectangleShape axis(sf::Vector2f(this->width, this->height / 3));
	axis.setPosition(sf::Vector2f(this->position.x, this->position.y + this->height / 3));
	axis.setFillColor(sf::Color::White);
	
	this->button.setPosition(this->buttonX - this->width / 10, this->position.y);
	this->button.setFillColor(sf::Color::Blue);

	window.draw(text);
	window.draw(axis);
	window.draw(button);
}

void Slider::logic(sf::RenderWindow& window)
{

	if (this->button.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)
		&& sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		this->moving = true;
	else if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		this->moving = false;
	if (this->moving)
	{
		if (this->getValue() > this->max)
			this->buttonX = this->max + this->position.x;
		else if (this->getValue() < this->min)
			this->buttonX = this->max + this->position.x;
		else if (sf::Mouse::getPosition(window).x <= this->position.x + this->width && sf::Mouse::getPosition(window).x >= this->position.x)
			this->buttonX = sf::Mouse::getPosition(window).x;
	}
}

sf::Vector2f Slider::getPosition()
{
	return this->position;
}