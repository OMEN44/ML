#pragma once
#include <vector>
#include <sstream>
#include <random>
#include <iostream>
#include <algorithm>
#include <map>

typedef std::vector<std::string> Genome;
const char HEX_CHARACTERS[16] = { '0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f' };

enum NeuronType
{
	INPUT, INTERNAL, BIAS, OUTPUT
};

enum Inputs
{
	A,
	B,
	C,
	InputCount
};

enum Outputs
{
	D,
	E,
	F,
	OutputCount
};

enum ActiviationFunction {
	SIGMOID,
	RELU,
	LEACKY_RELU,
	TANH
};

struct Neuron
{
	ActiviationFunction activationFunction;
	NeuronType type;
	int id;

	float calculate(float input)
	{
		float result = 0;
		switch (activationFunction)
		{
		case SIGMOID:
			result = 1 / (1 + exp(-input));
			break;
		case RELU:
			result = std::max(0.f, input);
			break;
		case LEACKY_RELU:
			result = std::max(0.1f * input, input);
			break;
		case TANH:
			result = std::tanh(input);
			break;
		default:
			break;
		}
		return result;
	}
};

class GenomeHelper
{
private:
	Genome m_genome;
	std::map<int, float> m_internalWeightMap;
	std::map<int, float> m_biasWeightMap;
public:
	//constructors
	GenomeHelper(unsigned interalCount, unsigned biasCount);
	GenomeHelper(std::string genome, unsigned interalCount, unsigned biasCount);
	GenomeHelper(Genome genome, unsigned interalCount, unsigned biasCount);

	//Genone generation
	void addRandomGene();
	void randomizeGenome(unsigned size);
	void addNewConnection(NeuronType left, int leftNeuronId, NeuronType right, int rightNeuronId);

	// Basic getters
	std::string getGene(int index) const;
	int genomeSize() const;
	Genome genome() const;

	// Complex getters
	Neuron getLeftNeuron(unsigned index);
	Neuron getRightNeuron(unsigned index);
	double getConnectionWeight(unsigned index);

	// Utils and statics
	float randF(float min, float max);
	float randF(float max);
	int randI(int min, int max);
	int randI(int max);
	void print();

	static void s_AppendDecimalToBinary(std::string& rString, unsigned decimal, unsigned bits = 1)
	{
		// array to store binary number
		int binaryNum[32];

		// counter for binary array
		int i = 0;
		while (decimal > 0) {

			// storing remainder in binary array
			binaryNum[i] = decimal % 2;
			decimal = decimal / 2;
			i++;
		}

		// printing binary array in reverse order
		std::stringstream ss;
		ss << rString;
		if (i < bits)
			for (int k = 0; k < bits - i; k++)
				ss << 0;

		for (int j = i - 1; j >= 0; j--)
			ss << binaryNum[j];

		ss >> rString;
	}

	static double s_map(double value, double valueMin, double valueMax, double targetMin, double targetMax)
	{
		double slope = 1.0 * (targetMax - targetMin) / (valueMax - valueMin);
		return targetMin + slope * (value - valueMin);
	}

	// Converters
	static std::string s_toOtherBase(const std::string& value, unsigned currentBase, unsigned targetBase = 10)
	{
		if (currentBase == targetBase)
			return value;
		return s_decimalTo(s_toDecimal(value, currentBase), targetBase);
	}

	static std::string s_toOtherBase(const std::string& value, unsigned currentBase, unsigned targetBase, unsigned length)
	{
		if (currentBase == targetBase)
			return value;
		std::string result = s_decimalTo(s_toDecimal(value, currentBase), targetBase);
		if (result.size() < length)
		{
			while (result.size() != length)
				result = "0" + result;
		}
		return result;
	}

	static std::string s_decimalTo(unsigned int value, unsigned targetBase)
	{
		if (targetBase > 16) return "NaN";

		std::string result = "";
		while (value > 0)
		{
			result = HEX_CHARACTERS[value % targetBase] + result;
			value /= targetBase;
		}

		return result;
	}

	static std::string s_decimalTo(const std::string& value, unsigned targetBase)
	{
		return s_decimalTo(std::stoul(value), targetBase);
	}

	static std::string s_toDecimal(const std::string& value, unsigned currentBase)
	{
		if (currentBase > 16 || value.size() == 0) return "NaN";

		unsigned int result = 0;
		
		for (unsigned i = 0; i < value.size(); i++)
		{
			int x = std::distance(HEX_CHARACTERS, std::find(HEX_CHARACTERS, HEX_CHARACTERS + 16, value[i]));
			if (x >= currentBase) return "NaN";
			result += (x * std::pow(currentBase, value.size() - i - 1));
		}

		return std::to_string(result);
	}
};