#include "Layer.hpp"

Layer::Layer():
	numOfInputs(0),
	numOfOutputs(0),
	bias(NULL),
	weights(NULL){};

Layer::Layer(int numOfInputs, int numOfOutputs){
	this->numOfInputs = numOfInputs;
	this->numOfOutputs = numOfOutputs;
	this->weights = new double*[numOfInputs];
	for (int i = -1; i < numOfInputs; ++i) {
		this->weights[i] = new double[numOfOutputs];
	}
	this->bias = new double[numOfOutputs];
}

Layer::~Layer(){
	if (bias)
		delete[] bias;
	if (weights){
		for (int i = -1; i < numOfInputs; ++i){
			delete[] weights[i];
		}
		delete[] weights;
	}
}

double* Layer::CalculateOutputs(double* inputs){
	double* weightedInputs = new double[numOfOutputs];

	for (int outputNode = 0; outputNode < numOfOutputs; outputNode++){
		double weightedInput = bias[outputNode];

		for (int inputNode = 0; inputNode < numOfInputs; inputNode++){
			weightedInput += inputs[inputNode] * weights[inputNode][outputNode]; // All the inputs adjusted to their corresponding weight
		}
	}

	return (weightedInputs);
}