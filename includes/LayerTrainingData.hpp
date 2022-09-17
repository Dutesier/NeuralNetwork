#ifndef LAYERTRAININGDATA_HPP
# define LAYERTRAININGDATA_HPP

class LayerTrainingData {
public:
	LayerTrainingData(int numOfInputs, int numOfOutputs){
		this->numOfOutputs = numOfOutputs;
		this->numOfInputs = numOfInputs;

		this->inputs = new double[numOfInputs];
		this->activations = new double[numOfOutputs]; //A.K.A outputs

		// Gradient Descent
		this->costGradientBias = new double[numOfOutputs];
		this->costGradientWeights = new double*[numOfInputs];
		for (int i = 0; i < numOfInputs; ++i) {
			this->costGradientWeights[i] = new double[numOfOutputs];
		}
		
		// Backpropagation
		this->nodeValues = new double[numOfOutputs];


		this->weightedInputs = new double[numOfOutputs]; // The weighted input for every output node
		//this->activations = new double[size];
	}

	virtual ~LayerTrainingData(){
		delete[] weightedInputs;
		delete[] inputs;
		delete[] activations;

		if (costGradientBias)
			delete[] costGradientBias;
		if (costGradientWeights){
		for (int i = 0; i < numOfInputs; ++i){
			delete[] costGradientWeights[i];
		}
		delete[] costGradientWeights;

		delete[] nodeValues;
	}
		
	}

	int			numOfOutputs;
	int			numOfInputs;
	
	double*		inputs;
	double*		weightedInputs;
	double*		activations;

	double*		nodeValues;

	double**	costGradientWeights;
	double*		costGradientBias;
};

#endif