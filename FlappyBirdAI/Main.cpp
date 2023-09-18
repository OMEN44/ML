#include <iostream>
#include <vector>

#include "Game.h"
#include "FlappyBirdGame.h"

int main()
{
	while (true)
	{
		FlappyBirdGame("Testing", -1).run();
	}
}




























































//#include <iostream>
//#include <SFML/graphics.hpp>
//#include <string>
//
//#include "Game.h"
//
//
//int main()
//{
//	Game game;
//	sf::RenderWindow window(sf::VideoMode(game.screenWidth, game.screenHeight), "Flappy?");
//	sf::Event e;
//	sf::Clock clock;
//	const float secondsPerFrame = 1.f / 40.f;
//	float accumulator = 0.f;
//
//	while (window.isOpen())
//	{
//		game.input(window, e);
//
//		float dt = clock.restart().asSeconds();
//		accumulator += dt;
//
//		while (accumulator >= secondsPerFrame)
//		{
//			game.update(secondsPerFrame);
//			accumulator -= secondsPerFrame;
//		}
//
//		window.clear(sf::Color::Black);
//		game.render(window);
//		window.display();
//	}
//
//	return 0;
//}