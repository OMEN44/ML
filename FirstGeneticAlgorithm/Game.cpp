#include "Game.h"

unsigned const int screenWidth = 400;
unsigned const int screenHeight = 600;
unsigned const int numOfMoves = 400;
unsigned const int population = 200;
unsigned const int pixelsPerStep = 10;
unsigned const int selectionSize = 5;
float mutationPercent = 2;
double pi = 3.14159265358979323846;

bool Game::isGenerationDead(std::vector<Dot> dots) {
	for (int i = 0; i < population; i++) {
		if (!dots[i].checkForDeath())
			return false;
	}
	return true;
}