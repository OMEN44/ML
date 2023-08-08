#include "GameEngine.h"

void GameEngine::logic()
{
	if (this->start == nullptr || this->finish == nullptr)
	{
		this->simulating = false;
		this->buttons["play"]->enable(false);
	}
	else
	{
		this->buttons["play"]->enable(true);
	}
	if (simulating && this->population.size() == 0)
		this->generatePopulation();
	if (simulating) {
		for (int i = 0; i < populationSize; i++)
			this->population[i].takeStep(this->finish, this->walls);
		if (this->generationDead())
		{
			std::sort(
				this->population.begin(),
				this->population.end(),
				[this](Dot& a, Dot& b) {
					return a.getFitness(this->finish) > b.getFitness(this->finish);
				}
			);

			//print the top 10
			std::for_each(this->population.begin(), this->population.begin() + 10,
				[this](Dot& dot) {
					std::cout << GameEngine::distance(*this->finish, dot.getPosition()) << " * " << dot.step << "/" << steps << " = " << dot.getFitness(this->finish) << std::endl;
				}
			);
			std::cout << std::endl;

			// select the fittest
			std::vector<Dot> fittest;
			std::copy(
				this->population.begin(),
				this->population.begin() + selectionSize,
				std::back_inserter(fittest)
			);
			this->population.clear();

			//Matate them >:)
			std::for_each(
				fittest.begin(),
				fittest.end(),
				[&](Dot& dot) {
					dot.mutate();
				}
			);

			//Breed them :|
			for (int i = 0; i < populationSize; i++)
			{
				std::vector<float> newMoves;
				for (int i = 0; i < steps; i++)
				{
					newMoves.push_back(fittest[Dot::randI(selectionSize - 1)].getStep(i));
				}
				this->population.push_back(Dot(*this->start, newMoves));
			}
		}
	}
}