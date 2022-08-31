#include "Node.hpp"

Node::Node():activationThreshold(0), activationStatus(0){};

Node::Node(double threshold){
	this->activationStatus = 0;
	this->activationThreshold = threshold;
}

void Node::tryActivate(double weightedInput){
	if (weightedInput >= activationThreshold) {
		activationStatus = 1;
	}
}

double Node::isActive(){
	return activationStatus;
}