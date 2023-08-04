#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Slider.h"
#include "GameEngine.h"

#include "Testing.h"

int main() {
	Testing t;
	sf::CircleShape* first = new sf::CircleShape(10);
	sf::CircleShape* second = new sf::CircleShape(10);
	sf::CircleShape* third = new sf::CircleShape(10);

	t.addEntity("first", first);
	t.addEntity("second", second);
	t.addEntity("third", third);

	t.deleteEntity("second");

	t.test();

	/*sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, sf::Style::None), "Genetic algorithm for solving mazes");

	sf::Event event;
	GameEngine game;

	sf::Font f;
	f.loadFromFile("C:\\Users\\huons\\OneDrive\\Documents\\programming\\Resources\\Arial.ttf");

	sf::Texture t;
	t.loadFromFile("C:\\Users\\huons\\OneDrive\\Documents\\programming\\Resources\\play.png");



	while (window.isOpen())
	{
		game.input(event, window);
		window.clear(sf::Color::Black);
		game.renderAll(window);
		window.display();
	}*/

	return 0;
}