#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "GameEngine.h"
#include "Slider.h"

int main() {

	sf::RenderWindow window(
		sf::VideoMode(
			static_cast<unsigned int>(SCREEN_WIDTH), 
			static_cast<unsigned int>(SCREEN_HEIGHT)
		), 
		"Genetic algorithm for solving mazes"
	);

	sf::Event event;
	GameEngine game;

	sf::Font f;
	f.loadFromFile("C:\\Users\\huons\\OneDrive\\Documents\\programming\\Resources\\Arial.ttf");

	while (window.isOpen())
	{
		game.input(event, window);
		window.clear(sf::Color::Black);
		game.renderAll(window);
		game.logic();
		window.display();
	}

	return 0;
}