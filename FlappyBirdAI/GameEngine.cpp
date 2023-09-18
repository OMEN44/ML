#include "Game.h"

float screenHeight = 800;
float screenWidth = 800;

Game::Game(std::string title, int frameRateLimit)
	: window(sf::VideoMode(screenWidth, screenHeight), title)
{
	if (frameRateLimit > -1)
		this->window.setFramerateLimit(frameRateLimit);
	deltaTime = sf::seconds(1.0f / 60.0f);
}

Game::~Game()
{
	//remove all objects
	std::for_each(
		this->uniqueObjects.begin(),
		this->uniqueObjects.end(),
		[](std::pair<std::string, RenderObject*> drawable) {
			delete drawable.second;
		}
	);
}

void Game::run()
{
	start();
	sf::Clock clock;
	sf::Time accumulator = sf::Time::Zero;

	while (this->window.isOpen())
	{
		if (!paused)
		{
			sf::Time frameTime = clock.restart();
			accumulator += frameTime;

			while (accumulator >= this->deltaTime)
			{
				this->beforeUpdate();
				this->onUpdate();
				accumulator -= this->deltaTime;
			}

			this->onRender();
		}
		else
		{
			this->pauseInput();
			this->pauseRender();
			this->pauseUpdate();
		}

		sf::Event e;
		while (this->window.pollEvent(e))
		{
			switch (e.type)
			{
			case sf::Event::Closed:
				this->window.close();
				break;
			case sf::Event::KeyPressed:
				this->onKeyPress(e);
				break;
			case sf::Event::KeyReleased:
				this->onKeyRelease(e);
				break;
			case sf::Event::Resized:
			{
				sf::Vector2f size(e.size.width, e.size.height);
				sf::FloatRect visibleArea(sf::Vector2f(0, 0), size);
				this->window.setView(sf::View(visibleArea));
				screenHeight = size.y;
				screenWidth = size.x;
			}
			default:
				this->onInput(e);
				break;
			}
		}
	}
}

void Game::end()
{
	this->window.close();
}

void Game::pause()
{
	this->paused = !this->paused;
	this->onPause();
}

void Game::addObject(std::string name, RenderObject* object)
{
	if (!this->uniqueObjects.count(name))
	{
		object->onCreate();
		this->uniqueObjects.insert(std::pair<std::string, RenderObject*>(name, object));
	}
	else std::cout << "Object already exists!" << std::endl;
}

void Game::delObject(std::string name)
{
	if (this->uniqueObjects.count(name))
		this->uniqueObjects.erase(name);
	else std::cout << "Object does not exist!" << std::endl;
}

RenderObject* Game::getObject(std::string name)
{
	if (this->uniqueObjects.count(name))
	{
		auto it = this->uniqueObjects.find(name);
		if (it != this->uniqueObjects.end())
			return it->second;
	}
	else std::cout << "Object does not exist!" << std::endl;
	return nullptr;
}

void Game::addObject(RenderObject* object)
{
	object->onCreate();
 	this->genericObjects.push_back(object);
}

bool Game::objectCollision(const RenderObject& object1, const RenderObject& object2)
{
	for (const auto& shape1 : object1.getBody()) {
		sf::FloatRect bounds1 = shape1->getGlobalBounds();
		for (const auto& shape2 : object2.getBody()) {
			sf::FloatRect bounds2 = shape2->getGlobalBounds();

			if (bounds1.intersects(bounds2))
				return true;
		}
	}
	return false;
}

bool Game::objectCollision(const std::string& objectName1, const std::string& objectName2)
{
	return this->objectCollision(*this->getObject(objectName1), *this->getObject(objectName2));
}

bool Game::objectCollisionWithGeneric(const std::string& objectName)
{
	for (const auto& genericObject : this->genericObjects)
	{
		for (const auto& shape1 : this->getObject(objectName)->getBody()) 
		{
			sf::FloatRect bounds1 = shape1->getGlobalBounds();
			for (const auto& shape2 : genericObject->getBody()) 
			{
				sf::FloatRect bounds2 = shape2->getGlobalBounds();

				if (bounds1.intersects(bounds2))
					return true;
			}
		}
	}
	return false;
}

std::vector<RenderObject*> Game::getGenericObjects()
{
	return this->genericObjects;
}

void Game::onUpdate()
{
	std::for_each(
		this->uniqueObjects.begin(),
		this->uniqueObjects.end(),
		[this](std::pair<std::string, RenderObject*> pair) {
			pair.second->onUpdate(this->deltaTime);
		}
	);
	std::for_each(
		this->genericObjects.begin(),
		this->genericObjects.end(),
		[this](RenderObject* object) {
			object->onUpdate(this->deltaTime);
		}
	);
}

void Game::onRender()
{
	window.clear(sf::Color::Black);
	std::for_each(
		this->uniqueObjects.begin(),
		this->uniqueObjects.end(),
		[this](std::pair<std::string, RenderObject*> pair) {
			pair.second->onRender(this->window);
		}
	);
	std::for_each(
		this->genericObjects.begin(),
		this->genericObjects.end(),
		[this](RenderObject* object) {
			object->onRender(this->window);
		}
	);
	window.display();
}

void Game::start() {}
void Game::beforeUpdate() {}
void Game::onInput(sf::Event& e) {}
void Game::onKeyRelease(sf::Event &e) {}
void Game::onKeyPress(sf::Event& e) {}


void Game::onPause() {}
void Game::pauseInput() {}
void Game::pauseRender() {}
void Game::pauseUpdate() {}
