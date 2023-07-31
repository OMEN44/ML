#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Slider.h"
#include "GameEngine.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Genetic algorithm for solving mazes");

	sf::Event event;
	GameEngine game;

	bool inBounds = false;
	int dotIndex = 0;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) 
			{
				window.close();
			}
			if (event.type == sf::Event::MouseEntered) inBounds = true;
			if (event.type == sf::Event::MouseLeft) inBounds = false;
			if (inBounds && event.type == sf::Event::MouseButtonPressed)
			{
				sf::CircleShape brush(20);
				brush.setFillColor(sf::Color::Green);
				brush.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)) + sf::Vector2f(-20, -20));
				game.addEntity(std::to_string(dotIndex), &brush);
				dotIndex++;
			}
			
		}

		window.clear(sf::Color::Black);
		game.render(window);
		window.display();
	}

	return 0;
}