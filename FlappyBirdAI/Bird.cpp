#include "Bird.h"

Bird::Bird()
{
	this->topology = { 2, 3, 3, 1 };
	this->reset();
	this->genRandomNetwork();
}

bool Bird::isDead()
{
	return this->dead;
}

sf::Vector2f Bird::getPosition()
{
	return this->position;
}

void Bird::setPosition(sf::Vector2f position)
{
	this->position = position;
}

void Bird::reset()
{
	this->dead = false;
	this->position = sf::Vector2f(100, 400);
	this->fitness = 0;
	this->velocity = 0;
}

unsigned Bird::getFitness()
{
	return this->fitness;
}

sf::Vector2f Bird::getPipeDistance(std::vector<RenderObject*> pipes)
{
	for (auto* pipe : pipes)
	{
		//if pipe infront of bird
		if (pipe->getPosition().x > 100)
		{
			return sf::Vector2f(pipe->getPosition().x - 100, this->position.y - pipe->getPosition().y - 100);
		}
	}
	//should never reach here unless there is no pipes exisiting
	return sf::Vector2f(0, 0);
}

std::vector<std::vector<std::vector<float>>> Bird::getWeights()
{
	return this->weights;
}

//std::vector<std::vector<float>> Bird::getBias()
//{
//	return this->neuronBias;
//}

void Bird::render(sf::RenderWindow& w)
{
	sf::CircleShape c(10);
	c.setFillColor(sf::Color::Yellow);
	c.setPosition(this->position + sf::Vector2f(10, 10));
	w.draw(c);
}

void Bird::update(std::vector<RenderObject*> pipes)
{
	//check for death
	for (auto* pipe : pipes)
	{
		if (this->position.x > pipe->getPosition().x - 30 && this->position.x < pipe->getPosition().x + 60)
		{
			if (this->position.y < pipe->getPosition().y || this->position.y > pipe->getPosition().y - 20 + dynamic_cast<Pipe*>(pipe)->getGapSize())
			{
				this->dead = true;
			}
		}
	}
	if (this->position.y > screenHeight)
		this->dead = true;


	if (this->dead)
	{
		this->position += sf::Vector2f(-2, 0);
	}
	else
	{
		this->velocity += 0.5;
		this->position += sf::Vector2f(0, this->velocity);
		if (this->feedForward(pipes) && this->position.y > 0)
			this->velocity = -10;
		// fitness is just based on how long each bird survives
		this->fitness++;
	}
}

void Bird::crossOver(std::vector<Bird> population)
{

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> mutationChance(0, 64);
	std::uniform_real_distribution<float> mutation(0, 1);
	//find the best of the population
	std::sort(
		population.begin(), 
		population.end(), 
		[](Bird& a, Bird& b)
		{
			return a.getFitness() > b.getFitness();
		}		
	);
	std::vector<std::vector<std::vector<std::vector<float>>>> bestWeights;
	std::for_each(
		population.begin(),
		population.begin() + 10,
		[&bestWeights](Bird& a)
		{
			bestWeights.push_back(a.getWeights());
		}
	);
	std::uniform_int_distribution<int> parentGene(0, bestWeights.size() - 1);

	for (int layer = 0; layer < this->weights.size(); layer++)
	{
		for (int neuron = 0; neuron < this->weights[layer].size(); neuron++)
		{
			for (int weight = 0; weight < this->weights[layer][neuron].size(); weight++)
			{
				this->weights[layer][neuron][weight] = bestWeights[parentGene(gen)][layer][neuron][weight];

				if (mutationChance(gen) == 0)
				{
					std::cout << "mutant" << std::endl;
					this->weights[layer][neuron][weight] * mutation(gen);
				}
			}
		}
	}

}

bool Bird::feedForward(std::vector<RenderObject*> pipes)
{
	sf::Vector2f inputs = this->getPipeDistance(pipes);
	std::vector<std::vector<float>> results;

	results.resize(this->topology.size());
	results[0].resize(this->topology[0]);
	results[0][0] = inputs.x;
	results[0][1] = inputs.y;
	// starting from the second layer iterate
	for (int layer = 1; layer < this->topology.size(); layer++)
	{
		//set depth of layer
		results[layer].resize(this->topology[layer]);
		// iterate through each neuron in each layer starting at layer 1
		for (int neuron = 0; neuron < this->topology[layer]; neuron++)
		{
			//get the sum of the product of each weight and input form the last layer
			float sum = 0;
			for (int weight = 0; weight < this->topology[layer - 1]; weight++)
			{
				//get the result from the previous layer and connected neuron
				//get the weight for the connection (layer - 1 is used becuase this vector does not have an input layer)
				sum += results[layer - 1][weight] * this->weights[layer - 1][neuron][weight];
			}
			results[layer][neuron] = std::max(0.2f * sum, sum);
			//results[layer][neuron] = 1.0f / (1.0f + exp(-sum));
		}
	}
	return results.back()[0] < 0;
}

void Bird::genRandomNetwork()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> distribution(-1, 1);
	
	// set size of layers excluding inputs
	this->weights.resize(this->topology.size() - 1);
	//iterate through layers excluding the first one
	for (int layer = 1; layer < this->topology.size(); layer++)
	{
		//set number of neurons in each layer
		this->weights[layer - 1].resize(this->topology[layer]);
		//iterate through neurons
		for (int neuron = 0; neuron < this->topology[layer]; neuron++)
		{
			//number of weights must be the same as the size of the previous layer
			this->weights[layer - 1][neuron].resize(this->topology[layer - 1]);
			for (int weight = 0; weight < this->topology[layer - 1]; weight++)
			{
				this->weights[layer - 1][neuron][weight] = distribution(gen);
			}
		}
	}
}
