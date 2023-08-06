#include "GameEngine.h"

float SCREEN_WIDTH = 800;
float SCREEN_HEIGHT = 800;
const int steps = 200;
const int populationSize = 40;
const int pixelsPerStep = 2;
const int selectionSize = 20;
const float mutationRate = 2;
const float pi = 3.1415926;

GameEngine::GameEngine()
{
	//generate population
	srand(static_cast<unsigned int>(time(0)));
	// Add buttons for sim
	this->buttons["play"] = new Button(0, 0, 40, 40, sf::Color::Blue, "C:\\Users\\huons\\OneDrive\\Documents\\programming\\Resources\\MazeGa\\play.png");
	this->buttons["reset"] = new Button(0, 0, 40, 40, sf::Color::Green, "C:\\Users\\huons\\OneDrive\\Documents\\programming\\Resources\\MazeGa\\reset.png");
	// add buttons for pen
	this->buttons["wall"] = new Button(0, 0, 30, 30, sf::Color::Blue, "C:\\Users\\huons\\OneDrive\\Documents\\programming\\Resources\\MazeGa\\wall.png");
	this->buttons["start"] = new Button(0, 0, 30, 30, sf::Color::Green, "C:\\Users\\huons\\OneDrive\\Documents\\programming\\Resources\\MazeGa\\start.png");
	this->buttons["finish"] = new Button(0, 0, 30, 30, sf::Color::Red, "C:\\Users\\huons\\OneDrive\\Documents\\programming\\Resources\\MazeGa\\finish.png");
	this->buttons["eraser"] = new Button(0, 0, 30, 30, sf::Color::White, "C:\\Users\\huons\\OneDrive\\Documents\\programming\\Resources\\MazeGa\\eraser.png");
	this->buttons["play"]->enable(false);
}

GameEngine::~GameEngine() {}

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
	std::sort(
		this->population.begin(),
		this->population.end(),
		[this](Dot& a, Dot& b) {
			return a.getFitness(this->finish) > b.getFitness(this->finish);
		}
	);
	if (this->population.size() == populationSize)
	{
		for (int i = 0; i < populationSize; i++)
		{
			sf::CircleShape dotDrawable(5);
			dotDrawable.setPosition(this->population[i].getPosition());
			sf::Color colour = sf::Color::Magenta;
			if (colour.a - i * 2 < 0)
				colour.a = 0;
			else
				colour.a -= i * 2;
			dotDrawable.setFillColor(colour);
			window.draw(dotDrawable);
		}
	}
}

void GameEngine::renderStaticObjects(sf::RenderWindow& window)
{
	//background
	sf::RectangleShape background(sf::Vector2f(SCREEN_WIDTH, 200));
	background.setFillColor(sf::Color(0x353535ff));
	background.setPosition(sf::Vector2f(0.0f, SCREEN_HEIGHT - 200.0f));

	//controll panel 1
	sf::RectangleShape panel1(sf::Vector2f(180, 180));
	panel1.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.0f - 185.0f, SCREEN_HEIGHT - 190.0f));
	panel1.setFillColor(sf::Color(0x263535ff));
	panel1.setOutlineColor(sf::Color::Black);
	panel1.setOutlineThickness(3);

	//controll panel 2
	sf::RectangleShape panel2(sf::Vector2f(180, 180));
	panel2.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.0f + 5.0f, SCREEN_HEIGHT - 190.0f));
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

void GameEngine::generatePopulation()
{
	float r = this->start->getRadius();
	for (int i = 0; i < populationSize; i++)
		this->population.push_back(Dot(this->start->getPosition() + sf::Vector2f(r/2, r/2)));
}

bool GameEngine::generationDead()
{
	for (Dot dot : this->population)
		if (dot.isAlive(this->finish))
			return false;
	return true;
}