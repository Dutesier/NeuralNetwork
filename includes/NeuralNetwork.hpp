#ifndef NEURALNETWORK_HPP
# define NEURALNETWORK_HPP

# include "Layer.hpp"
# include "Fruit.hpp"

class NeuralNetwork {
public:
	NeuralNetwork(int* layersSizes, int numOfLayers);
	virtual ~NeuralNetwork();
	void	Learn(Fruit *fruit, int numOfFruits, double learnRate);
	double *CalculateOutputs(double* inputs);
	int		Classify(double *inputs);
	double	Loss(Fruit& fruit);
	double	Loss(Fruit* fruit, int numOfFruits);
	void	ApplyAllGradients(double learnRate);
private:
	Layer**	layers;
	int		numOfLayers;
};

#endif