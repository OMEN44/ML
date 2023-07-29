#include "Dot.h"
#include "Utils.h"
#include "Game.h"
#include <cmath>

Dot::Dot() {
	this->step = 0;
	this->isDead = false;
	this->fitness = -1;
	this->x = screenWidth / 2;
	this->y = screenHeight - 35;
}

Dot::Dot(Utils* u) {
	this->step = 0;
	this->isDead = false;
	this->fitness = 0;
	this->x = screenWidth / 2;
	this->y = screenHeight - 35;

	this->moves = new float[numOfMoves];
	for (int i = 0; i < numOfMoves; i++)
		this->moves[i] = (*u).randF(360);
}

Dot::Dot(Utils* u, float* moves) {
	this->step = 0;
	this->isDead = false;
	this->fitness = 0;
	this->x = screenWidth / 2;
	this->y = screenHeight - 35;

	this->moves = moves;
}

void Dot::calculateFitness() {
	this->fitness = abs(1.0 / this->distanceFromGoal());
}

void Dot::takeStep(int numberOfSteps) {
	if (this->checkForDeath()) return;
	if (numberOfSteps + this->step > numOfMoves)
		this->isDead = true;
	else {
		this->step += numberOfSteps;
		this->x += pixelsPerStep * cos(this->moves[this->step] * (pi / 180));
		this->y += pixelsPerStep * sin(this->moves[this->step] * (pi / 180));
	}
}

void Dot::mutate(Utils* u) {
	for (int i = 0; i < numOfMoves; i++) {
		this->moves[i] *= (*u).randF(1 - (mutationPercent / 100), 1 + (mutationPercent / 100));
	}
}

bool Dot::checkForDeath() {
	// Dots will die if they reach the goal, run out of moves, or hit a wall.
	// They die alot lol.
	if (this->distanceFromGoal() <= 10
		|| this->step == numOfMoves
		|| this->x <= 0
		|| this->x >= screenWidth - 10
		|| this->y <= 0
		|| this->y >= screenHeight - 10)
		this->isDead = true;
	return this->isDead;
}

float Dot::getCurrentMove() {
	return this->moves[this->step];
}

float Dot::getMove(unsigned int step) {
	if (step > numOfMoves) return 0;
	return this->moves[step];
}

float* Dot::getPostition() {
	float coords[2] = { this->x, this->y };
	return coords;
}

void Dot::setPosition(float x, float y) {
	this->x = x;
	this->y = y;
}

float Dot::distanceFromGoal() {
	return sqrt(pow(this->x - (screenWidth / 2), 2) + pow(this->y - 50, 2));
}

float Dot::getFitness() {
	return this->fitness;
}