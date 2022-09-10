#ifndef NETWORKTRAININGDATA_HPP
# define NETWORKTRAININGDATA_HPP

# include "Layer.hpp"
# include "LayerTrainingData.hpp"

class NetworkTrainingData {
public:
	NetworkTrainingData(Layer** layers, int numOfLayers){
		trainingLayers = new LayerTrainingData*[numOfLayers];
		for (int i = 0; i < numOfLayers; ++i){
			trainingLayers[i] = new LayerTrainingData(*layers[i]);
		}
		numOfTrainingLayers = numOfLayers;
	}

	virtual ~NetworkTrainingData(){
		for (int i = 0; i < numOfTrainingLayers; ++i){
			delete trainingLayers[i];
		}
		delete[] trainingLayers;
	}

	LayerTrainingData**	trainingLayers;
	int					numOfTrainingLayers;
};

#endif