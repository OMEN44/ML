#include "goober.hpp"

Goober::Goober(sf::Vector2f position) : position(position)
{
	
}

void Goober::logic(float dt)
{
	
}

void Goober::draw(sf::RenderWindow& window)
{

	//create shape: 
	sf::CircleShape c(this->bodyRadius, 16);
	c.setOrigin(sf::Vector2f(bodyRadius, bodyRadius));
	c.setPosition(this->position);
	c.setFillColor(sf::Color::Blue);
	c.setRotation(this->direction);
	//c.setScale(this->streach, 1);

	float eyeRadius = this->bodyRadius * 0.3;
	float pupilRadius = this->bodyRadius * 0.1;

	window.draw(c);

	sf::CircleShape eye(eyeRadius);
	sf::CircleShape pupil(pupilRadius);
	eye.setFillColor(sf::Color::White);
	pupil.setFillColor(sf::Color::Black);
	sf::Vector2f eyePos(this->position);
	eyePos.x += this->bodyRadius * cos((-20 + this->direction) * (3.141592 / 180));
	eyePos.y += this->bodyRadius * sin((-20 + this->direction) * (3.141592 / 180));
	eye.setPosition(eyePos - sf::Vector2f(eyeRadius, eyeRadius));
	pupil.setPosition(eyePos - sf::Vector2f(eyeRadius, eyeRadius) + sf::Vector2f(2 * pupilRadius, 2 * pupilRadius));
	window.draw(eye);
	window.draw(pupil);

	eyePos = this->position;
	eyePos.x += this->bodyRadius * cos((20 + this->direction) * (3.141592 / 180));
	eyePos.y += this->bodyRadius * sin((20 + this->direction) * (3.141592 / 180));
	eye.setPosition(eyePos - sf::Vector2f(eyeRadius, eyeRadius));
	pupil.setPosition(eyePos - sf::Vector2f(eyeRadius, eyeRadius) + sf::Vector2f(2 * pupilRadius, 2 * pupilRadius));
	window.draw(eye);
	window.draw(pupil);
}

void Goober::setPosition(sf::Vector2f position)
{
	this->position = position;
}

void Goober::forward(float distance)
{
	this->position.x += distance * cos(this->direction * (3.141592 / 180));
	this->position.y += distance * sin(this->direction * (3.141592 / 180));


}

void Goober::rotate(float angle)
{
	this->direction += angle;
}
