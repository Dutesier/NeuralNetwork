#include "nn.hpp"

NeuralNetwork::NeuralNetwork(int* layersSizes, int numOfLayers){
	std::cout << "Creating Neural Network" << std::endl;
	this->numOfLayers = numOfLayers;
	this->layers = new Layer*[numOfLayers];
	for (int i = 0; i < numOfLayers; ++i){
		layers[i] = new Layer(layersSizes[i], layersSizes[i + 1]);
	}
}

double* NeuralNetwork::CalculateOutputs(double *inputs){
	for (int i = 0; i < numOfLayers; ++i){
		// Forward  Traversal
		inputs = layers[i]->CalculateOutputs(inputs);
	}
	return (inputs);
}

int		NeuralNetwork::Classify(double* inputs){
	std::cout << "Classifying Neural Network" << std::endl;
	double *outputs = CalculateOutputs(inputs);
	double max = MIN_VALUE;
	int	index = -1;
	for (int i = 0; i < layers[numOfLayers - 1]->getSize(); ++i){
		if (outputs[i] > max) {
			max = outputs[i];
			index = i;
		}
	}
	return (index);
}

NeuralNetwork::~NeuralNetwork(){
	std::cout << "Destroying Neural Network" << std::endl;
	if (layers) {
		for (int i = 0; i < numOfLayers; ++i) {
			delete layers[i];
		}
		delete[] layers;
	}
}

double	NeuralNetwork::Loss(Fruit& fruit){
	std::cout << "Calculating Single Loss" << std::endl;
	double* outputs = CalculateOutputs(fruit.traits);
	Layer* outputLayer = layers[numOfLayers - 1];
	double loss = 0;

	for (int outputNode = 0; outputNode < outputLayer->getSize(); ++outputNode){
		loss += outputLayer->NodeCost(outputs[outputNode], fruit.expectedResult[outputNode]);
	}
	std::cout << "Calculated Single Loss" << std::endl;

	return loss;
}

double	NeuralNetwork::Loss(Fruit *fruit, int numOfFruits){
	double totalLoss = 0;

	for (int i = 0; i < numOfFruits; ++i){
		totalLoss += Loss(fruit[i]);
	}

	return (totalLoss / numOfFruits);
}

void NeuralNetwork::Learn(Fruit* fruit, int numOfFruits, double learnRate){
	std::cout << "Neural Network --- Learning" << std::endl;
	const double change = 0.0000001;
	double originalLoss = Loss(fruit, numOfFruits);
	double deltaLoss;

	for (int lay = 0; lay < numOfLayers; ++lay){
		Layer* l = layers[lay];
		// Calculate cost gradient for weights
		for (int in = 0; in < l->getInputs(); ++in) {
			for (int out = 0; out < l->getSize(); ++out){
				l->setWeights(in, out, l->getWeights(in, out) + change);
				deltaLoss = Loss(fruit, numOfFruits) - originalLoss;
				l->setWeights(in, out, l->getWeights(in, out) - change);
				l->costGradientWeights[in][out] = deltaLoss / change;
			}
		}

		// Calculate cost gradient for biases
		for (int bi = 0; bi < l->getSize(); ++bi){
			l->setBias(bi, l->getBias(bi) + change);
			deltaLoss = Loss(fruit, numOfFruits) - originalLoss;
			l->setBias(bi, l->getBias(bi) - change);
			l->costGradientBias[bi] = deltaLoss / change;
		}
	}
	ApplyAllGradients(learnRate);
}

void	NeuralNetwork::ApplyAllGradients(double learnRate){
	std::cout << "Applying All Gradients" << std::endl;
	for (int lay = 0; lay < numOfLayers; ++lay){
		layers[lay]->ApplyGradients(learnRate);
	}
}