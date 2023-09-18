#include <iostream>
#include <SFML/graphics.hpp>
#include "goober.hpp"
#include "Game.h"
#include "GenomeHelper.h"

#include <string>

int main()
{


	sf::RenderWindow window(sf::VideoMode(1000, 600), "Title?");
	sf::Event e;
	sf::Clock clock;
	const float secondsPerFrame = 1.f / 2.f;
	float accumulator = 0.f;
	Game game;

	while (window.isOpen())
	{
		game.input(window, e);

		float dt = clock.restart().asSeconds();
		accumulator += dt;

		while (accumulator >= secondsPerFrame)
		{
			game.update(secondsPerFrame);
			accumulator -= secondsPerFrame;
		}

		window.clear(sf::Color::Black);
		game.render(window);
		window.display();
	}

	return 0;
}