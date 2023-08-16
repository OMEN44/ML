#include "GameEngine.h"

float SCREEN_WIDTH = 1000;
float SCREEN_HEIGHT = 800;
float mutationRate = 2;
int populationSize = 400;
int pixelsPerStep = 10;
int selectionSize = 20;
const float pi = 3.1415926;
const float steps = 200;

GameEngine::GameEngine()
{
	//generate population
	srand(static_cast<unsigned int>(time(0)));
	// Add buttons for sim
	this->buttons["play"] = new Button(0, 0, 40, 40, sf::Color::Blue, "C:\\Users\\huons\\OneDrive\\Documents\\programming\\Resources\\MazeGa\\play.png");
	this->buttons["reset"] = new Button(0, 0, 40, 40, sf::Color::Green, "C:\\Users\\huons\\OneDrive\\Documents\\programming\\Resources\\MazeGa\\reset.png");
	// add buttons for pen
	this->buttons["wall"] = new Button(0, 0, 40, 40, sf::Color::Blue, "C:\\Users\\huons\\OneDrive\\Documents\\programming\\Resources\\MazeGa\\wall.png");
	this->buttons["start"] = new Button(0, 0, 40, 40, sf::Color::Green, "C:\\Users\\huons\\OneDrive\\Documents\\programming\\Resources\\MazeGa\\start.png");
	this->buttons["finish"] = new Button(0, 0, 40, 40, sf::Color::Red, "C:\\Users\\huons\\OneDrive\\Documents\\programming\\Resources\\MazeGa\\finish.png");
	this->buttons["eraser"] = new Button(0, 0, 40, 40, sf::Color::White, "C:\\Users\\huons\\OneDrive\\Documents\\programming\\Resources\\MazeGa\\eraser.png");
	this->buttons["play"]->enable(false);
	//sliders
	this->sliders["population"] = new Slider(sf::Vector2f(350, SCREEN_HEIGHT - 25), "Population", 50, 1000);
	this->sliders["mutation"] = new Slider(sf::Vector2f(500, SCREEN_HEIGHT - 25), "Mutation rate", 1, 100);
	this->sliders["selection"] = new Slider(sf::Vector2f(650, SCREEN_HEIGHT - 25), "Selection size", 10, 100);
	this->sliders["step"] = new Slider(sf::Vector2f(800, SCREEN_HEIGHT - 25), "Step size", 1, 20);
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
		this->walls.begin(),
		this->walls.end(),
		[&window](sf::CircleShape* wall) {
			window.draw(*(wall));
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
			if (!this->population[i].isAlive())
				colour = sf::Color::Yellow;
			else if (colour.a - i < 0)
				colour.a = 0;
			else
				colour.a -= i;
			dotDrawable.setFillColor(colour);
			window.draw(dotDrawable);
		}
	}
	sf::CircleShape c(10);
	if (this->start != nullptr)
	{
		c.setPosition(*this->start);
		c.setFillColor(sf::Color::Green);
		window.draw(c);
	}
	if (this->finish != nullptr)
	{
		c.setPosition(*this->finish);
		c.setFillColor(sf::Color::Red);
		window.draw(c);
	}

}

void GameEngine::renderStaticObjects(sf::RenderWindow& window)
{
	//background
	sf::RectangleShape background(sf::Vector2f(SCREEN_WIDTH, 50));
	background.setFillColor(sf::Color(0x353535ff));
	background.setPosition(sf::Vector2f(0.0f, SCREEN_HEIGHT - 50.0f));

	window.draw(background);
	std::for_each(
		this->buttons.begin(),
		this->buttons.end(),
		[&](std::pair<std::string, Button*> keyValue) {
			sf::Vector2f position(0, 0);
			if (keyValue.first == "play")
				position = sf::Vector2f(5, SCREEN_HEIGHT - 45);
			else if (keyValue.first == "reset")
				position = sf::Vector2f(55, SCREEN_HEIGHT - 45);
			else if (keyValue.first == "eraser")
				position = sf::Vector2f(105, SCREEN_HEIGHT - 45);
			else if (keyValue.first == "finish")
				position = sf::Vector2f(155, SCREEN_HEIGHT - 45);
			else if (keyValue.first == "start")
				position = sf::Vector2f(205, SCREEN_HEIGHT - 45);
			else if (keyValue.first == "wall")
				position = sf::Vector2f(255, SCREEN_HEIGHT - 45);
			keyValue.second->setPosition(position);
			window.draw(keyValue.second->getDrawable());
		}
	);
	std::for_each(
		this->sliders.begin(),
		this->sliders.end(),
		[&](std::pair<std::string, Slider*> keyValue) {
			keyValue.second->setPosition(sf::Vector2f(keyValue.second->getPosition().x, SCREEN_HEIGHT - 25));
			keyValue.second->draw(window);
		}
	);
}

void GameEngine::generatePopulation()
{
	for (int i = 0; i < populationSize; i++)
		this->population.push_back(Dot(*this->start + sf::Vector2f(10/2, 10/2)));
}

bool GameEngine::generationDead()
{
	for (Dot dot : this->population)
		if (dot.isAlive(this->finish, this->walls))
			return false;
	return true;
}