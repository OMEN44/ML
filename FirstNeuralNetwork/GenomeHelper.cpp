#include "GenomeHelper.h"

GenomeHelper::GenomeHelper(unsigned interalCount, unsigned biasCount)
{
	srand(time(nullptr));
	m_genome.clear();
	for (int i = 0; i < interalCount; i++)
		this->m_internalWeightMap[i] = randF(-1, 1);
	for (int i = 0; i < biasCount; i++)
		this->m_biasWeightMap[i] = randF(-1, 1);
}

GenomeHelper::GenomeHelper(std::string genome, unsigned interalCount, unsigned biasCount) : GenomeHelper(interalCount, biasCount)
{
	for (unsigned i = 0; i < (genome.size() / 8); i++)
		this->m_genome.push_back(genome.substr(8 * i, 8));
}

GenomeHelper::GenomeHelper(Genome genome, unsigned interalCount, unsigned biasCount) : GenomeHelper(interalCount, biasCount)
{
	this->m_genome = genome;
}





// ===========================================
// Genone generation
// ===========================================

void GenomeHelper::addRandomGene()
{
	//hexadecimal characters
	std::string gene;

	std::stringstream ss;
	for (int i = 0; i < 8; i++)
	{
		ss << HEX_CHARACTERS[rand() % 16];
	}
	ss >> gene;

	this->m_genome.push_back(gene);
}

void GenomeHelper::randomizeGenome(unsigned size)
{
	this->m_genome.clear();
	for (unsigned i = 0; i < size; i++)
		this->addRandomGene();
}

//todo: The getters and setters must be updated to include the neuron ID.
//      Once this is done the getLayer function can be completed as the ids will be correct in the Genome.

void GenomeHelper::addNewConnection(NeuronType left, int leftNeuronId, NeuronType right, int rightNeuronId)
{
	std::string binaryGene = "";
	int neuronId = 0;
	if (left == INTERNAL || left == BIAS)
	{

	}
	s_AppendDecimalToBinary(binaryGene, left, 2);
	s_AppendDecimalToBinary(binaryGene, s_map(leftNeuronId, 0, ), 6);
	s_AppendDecimalToBinary(binaryGene, right, 2);
	s_AppendDecimalToBinary(binaryGene, leftNeuronId, 6);

	std::string hexGene = s_toOtherBase(binaryGene, 2, 16);

	//Add random weight
	for (int i = 0; i < 4; i++)
		hexGene = hexGene + HEX_CHARACTERS[rand() % 16];

	if (hexGene.size() != 8)
	{
		for (int i = 0; i < (9 - hexGene.size()); i++)
		{
			hexGene = "0" + hexGene;
		}
	}
	this->m_genome.push_back(hexGene);
}







// ===========================================
// Basic getters
// ===========================================


std::string GenomeHelper::getGene(int index) const
{
	return this->m_genome[index];
}

int GenomeHelper::genomeSize() const
{
	return this->m_genome.size();
}

Genome GenomeHelper::genome() const
{
	return this->m_genome;
}






// ===========================================
// Complex getters
// ===========================================

Neuron GenomeHelper::getLeftNeuron(unsigned index)
{
	if (this->genomeSize() <= index) return Neuron();
	std::string binaryNeuron = s_toOtherBase(this->m_genome[index].substr(0, 2), 16, 2, 8);

	Neuron n = {
		SIGMOID,
		NeuronType(std::stoi(s_toDecimal(binaryNeuron.substr(0, 2), 2))),
		std::stoi(s_toDecimal(binaryNeuron.substr(2, 6), 2))
	};

	return n;
}

Neuron GenomeHelper::getRightNeuron(unsigned index)
{
	if (this->genomeSize() <= index) return Neuron();
	std::string binaryNeuron = s_toOtherBase(this->m_genome[index].substr(2, 2), 16, 2, 8);

	Neuron n = {
		SIGMOID,
		NeuronType(std::stoi(s_toDecimal(binaryNeuron.substr(0, 2), 2))),
		std::stoi(s_toDecimal(binaryNeuron.substr(2, 6), 2))
	};

	return n;
}

double GenomeHelper::getConnectionWeight(unsigned index)
{
	if (this->m_genome.size() <= index) return 0;
	std::string hexWeight = this->m_genome[index].substr(4, 4);
	return s_map(std::stoul(s_toDecimal(hexWeight, 16)), 0, 65536, -5, 5);
}







// ===========================================
// Statics and utils
// ===========================================

float GenomeHelper::randF(float min, float max) {
	return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

float GenomeHelper::randF(float max) {
	return static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / max));
}

int GenomeHelper::randI(int min, int max) {
	return min + static_cast<int>(rand()) / (static_cast<int>(RAND_MAX / (max - min)));
}

int GenomeHelper::randI(int max) {
	return static_cast<int>(rand()) / (static_cast<int>(RAND_MAX / max));
}

void GenomeHelper::print()
{
	for (std::string s : this->m_genome)
		std::cout << s << " ";
	std::cout << std::endl;
	
	Neuron n;
	for (int i = 0; i < this->genomeSize(); i++)
	{
		std::cout << "\nGene number: " << i <<
			"\n+---+\t  " << this->getConnectionWeight(i) << "\t+---+"
			"\n| " << this->getLeftNeuron(i).type << " |-------------------| " << this->getRightNeuron(i).type << " |" <<
			"\n+---+\t\t\t+---+" <<
			"\n " << this->getLeftNeuron(i).id << "\t\t\t " << this->getRightNeuron(i).id
			<< std::endl;
	}
}
