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
	bool drawing = false;
	int dotIndex = 0;
	int brushSize = 10;

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
			if (event.type == sf::Event::MouseButtonPressed) drawing = true;
			if (event.type == sf::Event::MouseButtonReleased) drawing = false;

			if (event.type == sf::Event::MouseWheelMoved)
				if (event.mouseWheel.delta == 1 && brushSize != 40) brushSize++;
				else if (event.mouseWheel.delta == -1 && brushSize != 1) brushSize--;

			if (inBounds && drawing)
			{
				sf::CircleShape* brush = new sf::CircleShape(brushSize);
				brush->setFillColor(sf::Color::Green);
				brush->setPosition(sf::Vector2f(sf::Mouse::getPosition(window)) + sf::Vector2f(-brushSize, -brushSize));
				game.addEntity(std::to_string(dotIndex), brush);
				
				dotIndex++;
			}
			
		}

		window.clear(sf::Color::Black);
		game.render(window);
		window.display();
	}

	return 0;
}