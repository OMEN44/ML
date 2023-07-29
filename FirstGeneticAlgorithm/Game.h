#pragma once
#ifndef GAME_H
#define GAME_H
#include "Dot.h"
#include <vector>

extern unsigned const int numOfMoves, population, screenWidth, screenHeight, pixelsPerStep, selectionSize;
extern double pi;
extern float mutationPercent;

class Game {
public:
	bool isGenerationDead(std::vector<Dot> dots);
};


#endif // !GAME_H
