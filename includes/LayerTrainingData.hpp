#ifndef LAYERTRAININGDATA_HPP
# define LAYERTRAININGDATA_HPP

# include "Layer.hpp"

class LayerTrainingData {
public:
	LayerTrainingData(Layer& lay){
		this->myLayer = &lay;
		this->size = lay.getSize();
		this->weightedInputs = new double[size];
		//this->activations = new double[size];
		this->nodeValues = new double[size];
	}

	virtual ~LayerTrainingData(){
		delete[] weightedInputs;
		delete[] activations;
		delete[] nodeValues;
	}

	int		size;
	Layer*	myLayer;
	double	*weightedInputs;
	double	*activations;
	double	*nodeValues;
};

#endif