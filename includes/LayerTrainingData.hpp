#ifndef LAYERTRAININGDATA_HPP
# define LAYERTRAININGDATA_HPP

# include "Layer.hpp"

class LayerTrainingData {
public:
	LayerTrainingData(Layer& lay){
		this->weightedInputs = new double[lay.getSize()];
		this->activations = new double[lay.getSize()];
		this->nodeValues = new double[lay.getSize()];
	}

	virtual ~LayerTrainingData(){
		delete[] weightedInputs;
		delete[] activations;
		delete[] nodeValues;
	}

	double	*inputs;
	double	*weightedInputs;
	double	*activations;
	double	*nodeValues;
};

#endif