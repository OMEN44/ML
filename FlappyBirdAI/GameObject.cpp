#include "Game.h"

RenderObject::~RenderObject()
{
	std::for_each(
		this->body.begin(),
		this->body.end(),
		[](auto bodyMember) {
			delete bodyMember;
		}
	);
}

void RenderObject::move(sf::Vector2f distance)
{
	this->position += distance;
	std::for_each(
		this->body.begin(),
		this->body.end(),
		[distance](sf::Shape* bodyMember) {
			bodyMember->setPosition(bodyMember->getPosition() + distance);
		}
	);
}

void RenderObject::setPosition(sf::Vector2f position)
{
	std::for_each(
		this->body.begin(),
		this->body.end(),
		[this, position](sf::Shape* bodyMember) {
			bodyMember->setPosition(bodyMember->getPosition() - this->position + position);
		}
	);
	this->position = position;
}

void RenderObject::addBodyMember(sf::Shape* member)
{
	member->setPosition(member->getPosition() + this->position);
	this->body.push_back(member);
}

std::vector<sf::Shape*> RenderObject::getBody() const
{
	return this->body;
}

sf::Vector2f RenderObject::getPosition()
{
	return this->position;
}
