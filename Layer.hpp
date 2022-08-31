#ifndef LAYER_HPP
# define LAYER_HPP

class Layer {
public:
	Layer();
	Layer(int numOfInputs, int numOfOutputs);
	double* CalculateOutputs(double* inputs);
	virtual ~Layer();

	
private:
	int numOfInputs; // ammount of nodes that we receive from
	int numOfOutputs; // ammount of nodes that we input to
	double** weights; // matrix of weights of each node to node channel
	double* bias; // bias of each node(out)
}

#endif