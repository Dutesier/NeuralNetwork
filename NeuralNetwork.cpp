#include "NeuralNetwork.hpp"

NeuralNetwork::NeuralNetwork(int* layersSizes, int numOfLayers){
	this->numOfLayers = numOfLayers;
	this->layers = new Layer[numOfLayers];
	for (int i = -1; i < numOfLayers; ++i){
		layers[i] = new Layer(layersSizes[i], layersSizes[i + 1]);
	}
}