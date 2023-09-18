#include "Game.h"

unsigned screenHeight = 800;
unsigned screenWidth = 800;

Game::Game()
{
	n = new NeuralNetwork({4, 7, 2}, 7, 0);
	n->getGenome().print();
}

Game::~Game()
{
	delete n;
}

void Game::addObject(std::string name, sf::Drawable* object)
{
	if (!this->uniqueObjects.count(name))
		this->uniqueObjects.insert(std::pair<std::string, sf::Drawable*>(name, object));
	else
		cout << "Object already exists!" << endl;
}

void Game::delObject(std::string name)
{
	if (this->uniqueObjects.count(name))
		this->uniqueObjects.erase(name);
	else
		cout << "Object does not exist!" << endl;
}

sf::Drawable* Game::getObject(std::string name)
{
	if (this->uniqueObjects.count(name))
	{
		auto it = this->uniqueObjects.find(name);
		if (it != this->uniqueObjects.end())
			return it->second;
	}
	else
		cout << "Object does not exist!" << endl;
	return nullptr;
}

void Game::update(float dt)
{

}

void Game::render(sf::RenderWindow& w)
{
	sf::RectangleShape box(sf::Vector2f(800, 400));
	box.setFillColor(sf::Color::Black);
	box.setOutlineColor(sf::Color::Color(200, 200, 200));
	box.setOutlineThickness(5);
	box.setPosition(sf::Vector2f(40, 80));
	auto drawables = this->n->getDrawables(box);
	std::for_each(
		drawables.begin(),
		drawables.end(),
		[&w](auto drawable) {
			w.draw(*drawable);
			delete drawable;
		}
	);
}

void Game::input(sf::RenderWindow& w, sf::Event& e)
{
	while (w.pollEvent(e))
	{
		switch (e.type)
		{
		case sf::Event::Closed:
			w.close();
			break;
		case sf::Event::Resized:
			sf::FloatRect visibleArea(sf::Vector2f(0, 0), sf::Vector2f(e.size.width, e.size.height));
			w.setView(sf::View(visibleArea));
			screenHeight = e.size.height;
			screenWidth = e.size.width;
			break;
		}
	}
}
