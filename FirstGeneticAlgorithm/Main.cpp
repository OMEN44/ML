#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Dot.h"
#include "Game.h"
#include "Utils.h"
#include <cmath>
#include <algorithm>


//alocate memory for dynamic array
std::vector<Dot> dots;
bool simulate = false;
Game game;
Utils u;

void update() {

	for (int i = 0; i < population; i++) {
		dots[i].takeStep();
	}

	if (game.isGenerationDead(dots)) {
		//simulate = false;
		std::sort(dots.begin(), dots.end(),
			//This is a lambda function. This function is a comparator for the sorting algorithm.
			[](const Dot& a, const Dot& b) {
				return a.fitness > b.fitness;
			}
		);

		//print the top 10
		std::for_each(dots.begin(), dots.begin() + 10,
			[](const auto& dot) {
				std::cout << dot.fitness << std::endl;
			}
		);

		//select the fittest
		std::vector<Dot> fittest;
		std::copy(
			dots.begin(),
			dots.begin() + selectionSize,
			std::back_inserter(fittest)
		);
		//Kill old population:
		dots.clear();

		//Mutation
		std::for_each(
			fittest.begin(),
			fittest.end(),
			[&](Dot& dot) {dot.mutate(&u); }
		);

		for (int i = 0; i < population; i++) {
			float* moves = new float[numOfMoves];
			for (int i = 0; i < numOfMoves; i++)
				moves[i] = fittest[u.randI(0, selectionSize - 1)].getMove(i);
			dots.push_back(Dot(&u, moves));
		}

	}
}

int main() {
	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Basic genetic algorithm");

	sf::Event event;

	//initialize the array contents
	for (int i = 0; i < population; i++) {
		dots.push_back(Dot(&u));
	}

	//stage
	sf::CircleShape start(10);
	start.setPosition(screenWidth / 2 - 5, screenHeight - 40);
	sf::CircleShape finish(10);
	finish.setPosition(screenWidth / 2 - 5, 40);
	finish.setFillColor(sf::Color::Red);
	sf::RectangleShape runningFlag(sf::Vector2f(5, 5));

	int simulationBuffer = 0;

	while (window.isOpen())
	{

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::KeyReleased && sf::Keyboard::Space) {
				simulate = !simulate;
			}
		}

		window.clear(sf::Color::Black);
		if (simulate) {
			runningFlag.setFillColor(sf::Color::Green);
			if (simulationBuffer == 32) {
				//Loop runs in here
				update();
				simulationBuffer = 0;
			}
			simulationBuffer += 1;
		}
		else {
			runningFlag.setFillColor(sf::Color::Red);
		}


		window.draw(start);
		window.draw(finish);
		window.draw(runningFlag);

		sf::CircleShape currentDot(5);
		currentDot.setFillColor(sf::Color::Blue);

		//Find best for colouring
		Dot best;
		for (int i = 0; i < population; i++) {
			dots[i].calculateFitness();
			if (dots[i].getFitness() > best.getFitness()) {
				best = dots[i];
			}
		}

		for (int i = 0; i < population; i++) {
			float* xy = dots[i].getPostition();
			currentDot.setPosition(xy[0], xy[1]);
			if (dots[i].getFitness() == best.getFitness())
				currentDot.setFillColor(sf::Color::Green);
			else
				currentDot.setFillColor(sf::Color::Blue);
			window.draw(currentDot);
		}

		window.display();
	}

	return 0;
}