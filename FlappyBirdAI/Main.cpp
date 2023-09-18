#include <iostream>
#include <vector>

#include "Game.h"
#include "FlappyBirdGame.h"

int main()
{
	while (true)
	{
		Game* g = new FlappyBirdGame("Testing", 128);
		g->run();
	}
}







//#include <SFML/Graphics.hpp>
//#include <vector>
//
//const int WINDOW_WIDTH = 800;
//const int WINDOW_HEIGHT = 600;
//const float GRAVITY = 0.5f;
//const float JUMP_STRENGTH = 10.0f;
//const float PIPE_SPEED = 3.0f;
//
//class Bird {
//public:
//    Bird() {
//        birdSprite.setSize(sf::Vector2f(40, 40));
//        birdSprite.setPosition(100, WINDOW_HEIGHT / 2);
//    }
//
//    void flap() {
//        velocity = -JUMP_STRENGTH;
//    }
//
//    void update() {
//        velocity += GRAVITY;
//        birdSprite.move(0, velocity);
//    }
//
//    sf::RectangleShape birdSprite;
//    float velocity = 0;
//};
//
//class Pipe {
//    sf::RectangleShape pipeSpriteTop;
//    sf::RectangleShape pipeSpriteBottom;
//public:
//
//    Pipe(float x) {
//        pipeSpriteTop = sf::RectangleShape(sf::Vector2f(50, 600));
//        pipeSpriteBottom = sf::RectangleShape(sf::Vector2f(50, 600));
//        pipeSpriteTop.setFillColor(sf::Color::Green);
//        pipeSpriteBottom.setFillColor(sf::Color::Green);
//    }
//
//    void update() {
//        pipeSpriteTop.move(-PIPE_SPEED, 0);
//        pipeSpriteBottom.move(-PIPE_SPEED, 0);
//    }
//
//    void setPosition(float x, float y)
//    {
//        pipeSpriteTop.setPosition(x, y - 600);
//        pipeSpriteBottom.setPosition(x, y + 200);
//    }
//
//    sf::RectangleShape getSpriteTop()
//    {
//        return this->pipeSpriteTop;
//    }
//
//    sf::RectangleShape getSpriteBottom()
//    {
//        return this->pipeSpriteBottom;
//    }
//};
//
//int main() {
//    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Flappy Bird Clone");
//
//    Bird bird;
//    std::vector<Pipe> pipes;
//    sf::Clock clock;
//
//
//    while (window.isOpen()) {
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed) {
//                window.close();
//            }
//            if (event.type == sf::Event::KeyPressed) {
//                if (event.key.code == sf::Keyboard::Space) {
//                    bird.flap();
//                }
//            }
//        }
//
//        if (clock.getElapsedTime().asSeconds() > 1.5f) {
//            float randomY = rand() % 300 - 150; // Randomize pipe position
//            pipes.push_back(Pipe(WINDOW_WIDTH));
//            pipes.back().setPosition(WINDOW_WIDTH, WINDOW_HEIGHT / 2 + randomY);
//            clock.restart();
//        }
//
//        bird.update();
//
//        for (auto& pipe : pipes) {
//            pipe.update();
//
//            if (bird.birdSprite.getGlobalBounds().intersects(pipe.getSpriteTop().getGlobalBounds())
//                || bird.birdSprite.getGlobalBounds().intersects(pipe.getSpriteBottom().getGlobalBounds())) {
//                // Handle game over
//                while (true) {}
//            }
//        }
//
//        // Remove pipes that are out of screen
//        pipes.erase(
//            std::remove_if(
//                pipes.begin(), pipes.end(), [](Pipe& pipe) {
//                    return pipe.getSpriteTop().getPosition().x < -pipe.getSpriteTop().getGlobalBounds().width;
//                }
//            ), 
//            pipes.end()
//        );
//
//        window.clear();
//        window.draw(bird.birdSprite);
//
//        for (auto& pipe : pipes) {
//            window.draw(pipe.getSpriteTop());
//            window.draw(pipe.getSpriteBottom());
//        }
//
//        window.display();
//    }
//
//    return 0;
//}




























































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