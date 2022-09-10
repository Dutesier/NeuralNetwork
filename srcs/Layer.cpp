#include "Layer.hpp"


Layer::Layer():
	costGradientWeights(0),
	costGradientBias(0),
	numOfInputs(0),
	numOfOutputs(0),
	weights(0),
	bias(0){
	std::cout << "Creating Null Layer" << std::endl;
};

Layer::Layer(int numOfInputs, int numOfOutputs){
	std::cout << "Creating Layer" << std::endl;
	this->numOfInputs = numOfInputs;
	this->numOfOutputs = numOfOutputs;
	this->weights = new double*[numOfInputs];
	for (int i = 0; i < numOfInputs; ++i) {
		this->weights[i] = new double[numOfOutputs];
	}
	this->bias = new double[numOfOutputs];
	this->costGradientWeights = new double*[numOfInputs];
	for (int i = 0; i < numOfInputs; ++i) {
		this->costGradientWeights[i] = new double[numOfOutputs];
	}
	this->costGradientBias = new double[numOfOutputs];
	std::cout << "Created Layer" << std::endl;
}

Layer::~Layer(){
	std::cout << "Destroying Layer" << std::endl;
	if (bias)
		delete[] bias;
	if (weights){
		for (int i = 0; i < numOfInputs; ++i){
			delete[] weights[i];
		}
		delete[] weights;
	}
	if (costGradientBias)
		delete[] costGradientBias;
	if (costGradientWeights){
		for (int i = 0; i < numOfInputs; ++i){
			delete[] costGradientWeights[i];
		}
		delete[] costGradientWeights;
	}
}

double* Layer::CalculateOutputs(double* inputs){
	//std::cout << "Calculating Outputs from Layer" << std::endl;
	double* activations = new double[numOfOutputs];

	for (int outputNode = 0; outputNode < numOfOutputs; outputNode++){
		double weightedInput = bias[outputNode];

		for (int inputNode = 0; inputNode < numOfInputs; inputNode++){
			weightedInput += inputs[inputNode] * weights[inputNode][outputNode]; // All the inputs adjusted to their corresponding weight
		}
		activations[outputNode] = Activation(weightedInput);
	}

	return (activations);
}

double Layer::Activation(double weightedInput){
	return 1 / (1 + exp(-weightedInput)); //Sigmoid
}

// How much does the activation change with respect to the weighted input
double Layer::ActivationDerivative(double weightedInput){
	double activationValue = Activation(weightedInput);
	return activationValue * (1 - activationValue);
}

double Layer::NodeCost(double outputActivation, double expectedOutput){
	double error  = outputActivation - expectedOutput;
	return error * error;
}

// Partial derivative of how the Cost is affected by a change in output activation
double Layer::NodeCostDerivative(double outputActivation, double expectedOutput){
	return 2 * (outputActivation - expectedOutput);
}


Layer& Layer::operator=(const Layer& origin) { //  shallow copies
	if (bias)
		delete[] bias;
	if (weights){
		for (int i = 0; i < numOfInputs; ++i){
			delete[] weights[i];
		}
		delete[] weights;
	}
	if (costGradientBias)
		delete[] costGradientBias;
	if (costGradientWeights){
		for (int i = 0; i < numOfInputs; ++i){
			delete[] costGradientWeights[i];
		}
		delete[] costGradientWeights;
	}
	this->bias = origin.bias;
	this->weights = origin.weights;
	this->costGradientBias = origin.costGradientBias;
	this->costGradientWeights = origin.costGradientWeights;
	this->numOfInputs = origin.numOfInputs;
	this->numOfOutputs = origin.numOfOutputs;
	return (*this);
}

int Layer::getSize(){
	return numOfOutputs;
}

int Layer::getInputs(){
	return numOfInputs;
}

void Layer::setWeights(int inputNode, int outputNode, double  weight) {
	if (inputNode >= numOfInputs || outputNode >= numOfOutputs)
		return;
	if (inputNode < 0 || outputNode < 0)
		return;
	weights[inputNode][outputNode] = weight;
}

double Layer::getWeights(int inputNode, int outputNode){
	if (inputNode >= numOfInputs || outputNode >= numOfOutputs)
		return -42;
	return (weights[inputNode][outputNode]);
}

void Layer::setBias(int index, double bi) {
	if (index < 0 || index >= numOfOutputs)
		return;
	bias[index] = bi;
}

double Layer::getBias(int index){
	if (index < 0 || index >= numOfOutputs)
		return -42;
	return bias[index];
}


void Layer::InitializeRandomWeights(){
	for (int in = 0; in < numOfInputs; ++in){
		for (int out = 0; out < numOfOutputs; ++out) {
			double f = (double)rand() / RAND_MAX;
			weights[in][out] = (FMIN + f * (FMAX - FMIN)) / sqrt(numOfInputs);
		}
	}
}

void Layer::InitializeRandomBiases(){
	for (int out = 0; out < numOfOutputs; ++out){
		double f = (double)rand() / RAND_MAX;
		bias[out] = -(5) + f * (5 - (-5));
		bias[out] = f * (0); // Initializing to 0 for now
	}
}

void Layer::ApplyGradients(double learnRate){
	for (int outputNode = 0; outputNode < numOfOutputs; ++outputNode){
		// std::cout << "Bias[" << outputNode << "]: " << bias[outputNode] << std::endl;
		bias[outputNode] -= costGradientBias[outputNode] * learnRate;
		for (int inputNode = 0;  inputNode < numOfInputs; ++inputNode){
			weights[inputNode][outputNode] -= costGradientWeights[inputNode][outputNode] * learnRate;
			// std::cout << "Weights[" << inputNode << "][" << outputNode << "]: " << weights[inputNode][outputNode] << std::endl;
		}
	}
}
