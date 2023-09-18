#include "NeuralNetwork.h"
#include "Game.h"

NeuralNetwork::NeuralNetwork(const Topology& topology, unsigned internalNeurons, unsigned biasNeurons)
	: m_genomeHelper(internalNeurons, biasNeurons), m_topology(topology), m_linearNetwork(true)
{
	unsigned internalNeuronCount = 0;
	for (unsigned i = 0; i < m_topology.size() - 1; i++)
	{
		for (unsigned j = 0; j < m_topology[i]; j++)
		{
			for (unsigned k = 0; k < m_topology[i + 1]; k++)
			{
				if (m_topology.size() > 2)
				{
					if (!(i == 0 || i == (m_topology.size() - 2)))
						internalNeuronCount++;
					m_genomeHelper.addNewConnection(
						i == 0 ? INPUT : INTERNAL,
						i == 0 ? j : internalNeuronCount,
						i == (m_topology.size() - 2) ? OUTPUT : INTERNAL,
						i == (m_topology.size() - 2) ? j : internalNeuronCount
					);
				}
				else
					m_genomeHelper.addNewConnection(INPUT, j, OUTPUT, j);
			}
		}
	}
}

NeuralNetwork::NeuralNetwork(unsigned genomeSize, unsigned internalNeurons, unsigned biasNeurons)
	: m_genomeHelper(internalNeurons, biasNeurons), m_linearNetwork(false)
{

}

GenomeHelper NeuralNetwork::getGenome()
{
	return GenomeHelper(this->m_genomeHelper);
}

Layer NeuralNetwork::getLayer(unsigned index)
{
	Layer l;
	if (this->m_linearNetwork)
	{
		for (unsigned i = 0; i < this->m_topology[i]; i++)
		{
			
		}
	}

	return l;
}

void NeuralNetwork::feedForward(const std::vector<double>& inputValues)
{
	
}










std::vector<sf::Drawable*> NeuralNetwork::getDrawables(sf::RectangleShape& boundingBox)
{
	// Topology info
	uint16_t neuronCount = 0;
	for (int i = 0; i < this->m_topology.size(); i++)
		neuronCount += this->m_topology[i];
	
	// border box
	sf::Vector2f origin = boundingBox.getPosition();
	sf::Vector2f borderSize = boundingBox.getSize();
	std::vector<sf::Drawable*> drawables = {new sf::RectangleShape(boundingBox)};
	if (!this->m_linearNetwork) return drawables;

	// circles
	float circleRadius = sqrt(((borderSize.x * borderSize.y) / neuronCount) / 32);
	sf::CircleShape neuronShape(circleRadius);
	neuronShape.setFillColor(sf::Color::Blue);

	//connections
	sf::RectangleShape connectionShape;

	// generate drawables:
	uint32_t connectionCount = 0;
	for (int layer = 0; layer < this->m_topology.size(); layer++)
	{
		for (int neuron = 0; neuron < this->m_topology[layer]; neuron++)
		{
			// current neuron position
			sf::Vector2f neuronPosLeft(
				borderSize.x / (this->m_topology.size() + 1) * (layer + 1) + origin.x - circleRadius,
				borderSize.y / (this->m_topology[layer] + 1) * (neuron + 1) + origin.y - circleRadius
			);
			if (layer < this->m_topology.size() - 1)
			{
				for (int connection = 0; connection < this->m_topology[layer + 1]; connection++)
				{
					//other neuron position
					sf::Vector2f neuronPosRight(
						borderSize.x / (this->m_topology.size() + 1) * (layer + 2) + origin.x - circleRadius,
						borderSize.y / (this->m_topology[layer + 1] + 1) * (connection + 1) + origin.y - circleRadius + 5
					);
					//set rotation
					connectionShape.setRotation(atan((neuronPosLeft.y - neuronPosRight.y) / (neuronPosLeft.x - neuronPosRight.x)) * (180.0 / 3.14159265359));
					//set position
					connectionShape.setPosition(neuronPosLeft + sf::Vector2f(7 * circleRadius / 8, 7 * circleRadius / 8));
					//set size
					connectionShape.setSize(sf::Vector2f(
						std::sqrt((neuronPosLeft.y - neuronPosRight.y) * (neuronPosLeft.y - neuronPosRight.y) + (neuronPosLeft.x - neuronPosRight.x) * (neuronPosLeft.x - neuronPosRight.x)),
						(circleRadius / 4) * (this->getGenome().getConnectionWeight(connectionCount) / 3)
					));
					//set colour
					connectionShape.setFillColor(this->getGenome().getConnectionWeight(connectionCount) > 0. ? sf::Color::Green : sf::Color::Red);

					drawables.push_back(new sf::RectangleShape(connectionShape));
					connectionCount++;
				}
			}
			// add neuron
			neuronShape.setPosition(neuronPosLeft);
			drawables.push_back(new sf::CircleShape(neuronShape));
		}
	}

	return drawables;
}