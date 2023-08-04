#include "GameEngine.h"
#include <iostream>

unsigned short int SCREEN_WIDTH = 800;
unsigned short int SCREEN_HEIGHT = 800;

GameEngine::GameEngine()
{
	// Add buttons for sim
	this->buttons["play"] = new Button(0, 0, 40, 40, sf::Color::Blue, "C:\\Users\\huons\\OneDrive\\Documents\\programming\\Resources\\play.png");
	this->buttons["reset"] = new Button(0, 0, 40, 40, sf::Color::Green, "C:\\Users\\huons\\OneDrive\\Documents\\programming\\Resources\\play.png");
	// add buttons for pen
	this->buttons["wall"] = new Button(0, 0, 30, 30, sf::Color::Blue, "C:\\Users\\huons\\OneDrive\\Documents\\programming\\Resources\\play.png");
	this->buttons["start"] = new Button(0, 0, 30, 30, sf::Color::Green, "C:\\Users\\huons\\OneDrive\\Documents\\programming\\Resources\\play.png");
	this->buttons["finish"] = new Button(0, 0, 30, 30, sf::Color::Red, "C:\\Users\\huons\\OneDrive\\Documents\\programming\\Resources\\play.png");
	this->buttons["eraser"] = new Button(0, 0, 30, 30, sf::Color::White, "C:\\Users\\huons\\OneDrive\\Documents\\programming\\Resources\\play.png");
}

GameEngine::~GameEngine() {
	std::for_each(
		this->entities.begin(),
		this->entities.end(),
		[&](std::pair<std::string, sf::Drawable*> keyValue) {
			if (auto circleShape = dynamic_cast<sf::CircleShape*>(this->getEntity(keyValue.first))) {
				std::cout << "It's a CircleShape! " << circleShape->getRadius() << std::endl;

				// Do something specific to CircleShape.
			}
	// Use dynamic_cast again to check if it's a RectangleShape.
			else if (auto rectangleShape = dynamic_cast<sf::RectangleShape*>(this->getEntity(keyValue.first))) {
				std::cout << "It's a RectangleShape!" << std::endl;
				// Do something specific to RectangleShape.
			}
			else {
				std::cout << "It's neither a CircleShape nor a RectangleShape." << std::endl;
			}
		}
	);
}

void GameEngine::renderAll(sf::RenderWindow& window)
{
	this->renderDynamicObjects(window);
	this->renderStaticObjects(window);
}

void GameEngine::renderDynamicObjects(sf::RenderWindow& window)
{
	std::for_each(
		this->entities.begin(),
		this->entities.end(),
		[&](std::pair<std::string, sf::Drawable*> keyValue) {
			window.draw(*(this->getEntity(keyValue.first)));
		}
	);
}

void GameEngine::renderStaticObjects(sf::RenderWindow& window)
{
	//background
	sf::RectangleShape background(sf::Vector2f(SCREEN_WIDTH, 200));
	background.setFillColor(sf::Color(0x353535ff));
	background.setPosition(sf::Vector2f(0, SCREEN_HEIGHT - 200));

	//controll panel 1
	sf::RectangleShape panel1(sf::Vector2f(180, 180));
	panel1.setPosition(sf::Vector2f(SCREEN_WIDTH / 2 - 185, SCREEN_HEIGHT - 190));
	panel1.setFillColor(sf::Color(0x263535ff));
	panel1.setOutlineColor(sf::Color::Black);
	panel1.setOutlineThickness(3);

	//controll panel 2
	sf::RectangleShape panel2(sf::Vector2f(180, 180));
	panel2.setPosition(sf::Vector2f(SCREEN_WIDTH / 2 + 5, SCREEN_HEIGHT - 190));
	panel2.setFillColor(sf::Color(0x263535ff));
	panel2.setOutlineColor(sf::Color::Black);
	panel2.setOutlineThickness(3);


	if (this->showControllPanel)
	{
		window.draw(background);
		window.draw(panel1);
		window.draw(panel2);
		std::for_each(
			this->buttons.begin(),
			this->buttons.end(),
			[&](std::pair<std::string, Button*> keyValue) {
				sf::Vector2f position(0, 0);
				if (keyValue.first == "play")
					position = sf::Vector2f(SCREEN_WIDTH / 2 - 175, SCREEN_HEIGHT - 60);
				else if (keyValue.first == "reset")
					position = sf::Vector2f(SCREEN_WIDTH / 2 - 125, SCREEN_HEIGHT - 60);
				else if (keyValue.first == "eraser")
					position = sf::Vector2f(SCREEN_WIDTH / 2 + 20, SCREEN_HEIGHT - 50);
				else if (keyValue.first == "finish")
					position = sf::Vector2f(SCREEN_WIDTH / 2 + 60, SCREEN_HEIGHT - 50);
				else if (keyValue.first == "start")
					position = sf::Vector2f(SCREEN_WIDTH / 2 + 100, SCREEN_HEIGHT - 50);
				else if (keyValue.first == "wall")
					position = sf::Vector2f(SCREEN_WIDTH / 2 + 140, SCREEN_HEIGHT - 50);
				keyValue.second->setPosition(position);
				window.draw(keyValue.second->getDrawable());
			}
		);
	}
}

void GameEngine::input(sf::Event& e, sf::RenderWindow& window)
{
	while (window.pollEvent(e))
	{
		switch (e.type) {
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::MouseEntered:
			this->inBounds = true;
			break;
		case sf::Event::MouseLeft:
			this->inBounds = false;
			break;
		case sf::Event::MouseButtonPressed:
			if (this->showControllPanel)
			{
				std::for_each(
					this->buttons.begin(),
					this->buttons.end(),
					[&](std::pair<std::string, Button*> keyValue)
					{
						if (keyValue.second->getDrawable().getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
						{
							std::cout << keyValue.first << std::endl;
							if (keyValue.first == "play")
							{
								//this->showControllPanel = !this->showControllPanel;
							}
							else if (keyValue.first == "reset")
							{

							}
							else if (keyValue.first == "eraser")
							{
								this->penColour = sf::Color::White;
							}
							else if (keyValue.first == "start")
							{
								this->penColour = sf::Color::Green;
							}
							else if (keyValue.first == "finish")
							{
								this->penColour = sf::Color::Red;
							}
							else if (keyValue.first == "wall")
							{
								this->penColour = sf::Color::Blue;
							}
						}
					});
			}
			else
			{
				this->drawing = true;
			}
			break;
		case sf::Event::MouseButtonReleased:
			this->drawing = false;
			break;
		case sf::Event::MouseWheelMoved:
			if (e.mouseWheel.delta == 1 && this->brushSize != 40) this->brushSize++;
			else if (e.mouseWheel.delta == -1 && this->brushSize != 1) this->brushSize--;
			break;
		case sf::Event::Resized:
		{
			sf::FloatRect visibleArea(sf::Vector2f(0, 0), sf::Vector2f(e.size.width, e.size.height));
			window.setView(sf::View(visibleArea));
			SCREEN_HEIGHT = e.size.height;
			SCREEN_WIDTH = e.size.width;
		}
		break;
		case sf::Event::KeyPressed:
			switch (e.key.code)
			{
			case sf::Keyboard::Space:
				this->showControllPanel = !this->showControllPanel;
				break;
			}
			break;
		}



		if (this->inBounds && this->drawing && !this->showControllPanel)
		{
			if (this->penColour == sf::Color::White)
			{
				std::for_each(
					this->entities.begin(),
					this->entities.end(),
					[&](std::pair<std::string, sf::Drawable*> keyValue) {
						if (auto circleShape = dynamic_cast<sf::CircleShape*>(this->getEntity(keyValue.first))) {
							int r = circleShape->getRadius();
							if (GameEngine::distance(circleShape->getPosition() + sf::Vector2f(r, r), sf::Vector2f(sf::Mouse::getPosition(window))) < r) {
								std::cout << keyValue.first << std::endl;
								std::cout << this->getEntity(keyValue.first) << ": from get" << std::endl;
								
								this->entities.erase(keyValue.first);
							}
						}
					}
				);
			}
			else
			{
				sf::CircleShape* brush = new sf::CircleShape(this->brushSize);
				brush->setFillColor(this->penColour);
				brush->setPosition(sf::Vector2f(sf::Mouse::getPosition(window)) + sf::Vector2f(-this->brushSize, -this->brushSize));
				this->addEntity(std::to_string(dotIndex), brush);
				dotIndex++;
			}
			
		}

	}
}

void GameEngine::logic()
{

}

void GameEngine::addEntity(std::string name, sf::Drawable* entity)
{
	if (!this->entities.count(name))
	{
		this->entities[name] = entity;
	}
	else
	{
		std::cout << "Didn't add entity: " << name << " Becuase it already exists." << std::endl;
	}
}

void GameEngine::deleteEntity(std::string name)
{
	auto it = this->entities.find(name);
	if (it != this->entities.end())
	{
		this->entities.erase(it);
	}
}

sf::Drawable* GameEngine::getEntity(std::string name)
{
	auto it = this->entities.find(name);
	return (it != this->entities.end()) ? it->second : nullptr;
}