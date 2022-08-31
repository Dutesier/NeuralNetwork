#ifndef NEURALNETWORK_HPP
# define NEURALNETWORK_HPP

# include "Layer.hpp"

class NeuralNetwork {
public:
	NeuralNetwork(int* layersSizes, int numOfLayers);
private:
	Layer*	layers;
	int		numOfLayers;
}

#endif