#ifndef LAYER_HPP
# define LAYER_HPP
# include <random>
# include <iostream>
# include <cmath>
const double MIN_VALUE = -1;
const double FMIN = -1;
const double FMAX = 1;

class Layer {
public:
	Layer();
	Layer(int numOfInputs, int numOfOutputs);
	virtual ~Layer();

	Layer& operator=(const Layer& origin);

	double* CalculateOutputs(double* inputs);
	double	Activation(double weightedInput);
	double	ActivationDerivative(double weightedInput);
	double	NodeCost(double outputActivation, double expectedOutput);
	double	NodeCostDerivative(double outputActivation, double expectedOutput);
	void	ApplyGradients(double learnRate);

	int		getSize();
	int		getInputs();
	double	getWeights(int inputNode, int outputNode);
	void	setWeights(int inputNode, int outputNode, double  weight);
	void	InitializeRandomWeights();
	void	InitializeRandomBiases();
	void	setBias(int index, double bi);
	double	getBias(int index);

	
	double**	costGradientWeights;
	double*		costGradientBias;
private:
	// Attributes
	int numOfInputs; // ammount of nodes that we receive from
	int numOfOutputs; // ammount of nodes that we input to
	double** weights; // matrix of weights of each node to node channel
	double* bias; // bias of each node(out)
};

#endif