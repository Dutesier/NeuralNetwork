#include "Fruit.hpp"
#include <iostream>

Fruit::Fruit(){
	double f = (double)rand() / RAND_MAX;
	ammountOfSpots = 0 + f * (25 - 0);
	double d = (double)rand() / RAND_MAX;
	lenOfLeaves = 0 + d * (25 - 0);
	poisonous = (rand() % 2 != 0 ? 1 : 0);
	this->traits = new double[2];
	this->traits[0] = ammountOfSpots;
	this->traits[1] = lenOfLeaves;
	this->expectedResult = new double[2];
	this->expectedResult[0] = (poisonous);
	this->expectedResult[1] = (!poisonous);
};

Fruit::Fruit(double spots, double leaves, bool poison){
	this->ammountOfSpots = spots;
	this->lenOfLeaves = leaves;
	this->poisonous = poison;
	this->traits = new double[2];
	this->traits[0] = spots;
	this->traits[1] = leaves;
	this->expectedResult = new double[2];
	this->expectedResult[0] = (poisonous);
	this->expectedResult[1] = (!poisonous);
}

Fruit::~Fruit(){
	delete[] traits;
	delete[] expectedResult;
}

bool Fruit::isPoisonous(){
	return poisonous;
}