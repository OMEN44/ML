#pragma once
#ifndef DOT_H
#define DOT_H
#include "Utils.h"
#include <vector>

class Dot {
	float* moves;
	int step;
	bool isDead;
	float x, y;
public:
	float fitness = 0;
	Dot();
	Dot(Utils* u);
	Dot(Utils* u, float* moves);
	void calculateFitness();
	void takeStep(int numberOfSteps = 1);
	void mutate(Utils* u);
	void setPosition(float x, float y);
	bool checkForDeath();
	float getCurrentMove();
	float getMove(unsigned int step);
	float distanceFromGoal();
	float getFitness();
	float* getPostition();
};

#endif // !DOT_H
