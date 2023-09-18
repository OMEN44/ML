#pragma once
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "GenomeHelper.h"

typedef std::vector<int> Topology;
typedef std::vector<Neuron> Layer;

class NeuralNetwork
{
	
	GenomeHelper m_genomeHelper;
	const Topology m_topology;
	bool m_linearNetwork;
	std::vector<Neuron> NeuronStates;
	Layer getLayer(unsigned index);
public:
	NeuralNetwork(const Topology& topology, unsigned internalNeurons, unsigned biasNeurons);
	NeuralNetwork(unsigned genomeSize, unsigned internalNeurons, unsigned biasNeurons);
	void feedForward(const std::vector<double>& inputValues);

	GenomeHelper getGenome();


	//drawing Util
	std::vector<sf::Drawable*> getDrawables(sf::RectangleShape& boundingBox);
};

