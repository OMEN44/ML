#include "Player.h"

Player::Player() : RenderObject(sf::Vector2f(100, 400))
{

}

void Player::onCreate()
{
	sf::RectangleShape r(sf::Vector2f(40, 40));
	r.setPosition(0, 10);
	r.setFillColor(sf::Color::Color(250, 230, 150));
	this->addBodyMember(new sf::RectangleShape(r));
	sf::RectangleShape head(sf::Vector2f(20, 20));
	head.setPosition(30, 0);
	head.setFillColor(sf::Color::Color(250, 230, 75));
	this->addBodyMember(new sf::RectangleShape(head));
	sf::CircleShape wing(30);
	wing.setPosition(5, 20);
	wing.setFillColor(sf::Color::Color(250, 230, 75));
	wing.setScale(0.5, 0.25);
	wing.setOutlineColor(sf::Color::Black);
	wing.setOutlineThickness(6);
	this->addBodyMember(new sf::CircleShape(wing));
	this->isAlive = true;
}

void Player::onUpdate(sf::Time deltaTime)
{
	this->velocity += 0.5;
	this->move(sf::Vector2f(0, this->velocity));
}

void Player::flap()
{
	this->velocity = -7;
}
