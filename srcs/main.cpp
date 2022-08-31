#include "nn.hpp"

int main(void){
	std::srand(std::time(nullptr));
	int sizes[3] = {2, 3, 2};
	double inputs[2] = {0, 1};
	Fruit* fruitSalad = new Fruit[100];

	NeuralNetwork network(sizes, 2);
	network.Learn(fruitSalad, 100, 0.02);
	std::cout << network.Classify(inputs) << std::endl;
	delete[] fruitSalad;
}