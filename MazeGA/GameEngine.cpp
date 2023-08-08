#include "GameEngine.h"

float SCREEN_WIDTH = 800;
float SCREEN_HEIGHT = 800;
const int populationSize = 400;
const int pixelsPerStep = 10;
const int selectionSize = 20;
const float mutationRate = 2;
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