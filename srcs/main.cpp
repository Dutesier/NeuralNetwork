#include "nn.hpp"
#include "Fruit.hpp"

const int SAMPLE_SIZE = 250;

void PrintFruits(Fruit* array, int len){
	int printable[50][50];
	int leaf, spot;

	for (int y = 0; y < 50; ++y) {
		for (int x = 0; x < 50; ++x){
			printable[x][y] = 0;
		}
	}

	for (int i = 0; i < len; ++i){
		leaf = array[i].traits[1] * 2;
		spot = array[i].traits[0] * 2;
		printable[leaf][spot] = (array[i].isPoisonous() == true ? 2:1);
	}

	std::cout << "Spots" << std::endl;
	for (int y = 49; y >= 0; --y){
		if (y < 10)
			std::cout << " ";
		std::cout << y << " | ";
		for (int x = 0; x < 50; ++x){
			if (printable[x][y] == 2)
				std::cout << "\033[41;1mP\033[0m ";
			else if (printable[x][y] == 1)
				std::cout << "\033[42;1mS\033[0m ";
			else
				std::cout << ". ";
		}
		std::cout << std::endl;
	}
	std::cout << "     ";
	for (int y = 0; y < 50; ++y) {
		std::cout << y;
		if (y < 10)
			std::cout << " ";
	}

	std::cout << std::endl << "Leaves" << std::endl;
}

void PrintClassify(NeuralNetwork<Fruit>& network){
	int classified;
	double inputs[2];

	// std::cout << "Spots" << std::endl;
	for (double y = 49; y >= 0; --y){
		if (y < 10)
			std::cout << " ";
		std::cout << y << " | ";
		for (double x = 0; x < 50; ++x){
			inputs[0] = y;
			inputs[1] = x;
			classified = network.Classify(inputs);
			if (classified == 1)
				std::cout << "\033[42;1m \033[0m ";
			else if (classified == 0)
				std::cout << "\033[41;1m \033[0m ";
			else
				std::cout << ". ";
		}
		std::cout << std::endl;
	}
	std::cout << "     ";
	for (int y = 0; y < 50; ++y) {
		std::cout << y;
		if (y < 10)
			std::cout << " ";
	}
	std::cout << "\033[50A";
	// std::cout << std::endl << "Leaves\033[48A";
}

void MeasureAccuracy(Fruit* array, int len, NeuralNetwork<Fruit>& network){
	int classified;
	double inputs[2];
	int printable[50][50];
	int leaf, spot;

	for (int y = 0; y < 50; ++y) {
		for (int x = 0; x < 50; ++x){
			printable[x][y] = 0;
		}
	}

	for (int i = 0; i < len; ++i){
		leaf = array[i].traits[1] * 2;
		spot = array[i].traits[0] * 2;
		printable[leaf][spot] = (array[i].isPoisonous() == true ? 2:1);
	}

	std::cout << "Spots" << std::endl;
	for (double y = 49; y >= 0; --y){
		if (y < 10)
			std::cout << " ";
		std::cout << y << " | ";
		for (double x = 0; x < 50; ++x){
			inputs[0] = y;
			inputs[1] = x;
			classified = network.Classify(inputs);
			if (classified == 1) {
				if (printable[int(x)][int(y)] == 2)
					std::cout << "\033[41;1mS\033[0m ";//Wrong safe prediction
				else if (printable[int(x)][int(y)] == 1)
					std::cout << "\033[42;1mS\033[0m ";
				else
					std::cout << "\033[42;1m \033[0m ";
			}
			else if (classified == 0)
			{
				if (printable[int(x)][int(y)] == 1)
					std::cout << "\033[42;1mP\033[0m ";//Wrong poisonous prediction
				else if (printable[int(x)][int(y)] == 2)
					std::cout << "\033[41;1mP\033[0m ";
				else
					std::cout << "\033[41;1m \033[0m ";

			}
			else
				std::cout << ". ";
		}
		std::cout << std::endl;
	}
	std::cout << "     ";
	for (int y = 0; y < 50; ++y) {
		std::cout << y;
		if (y < 10)
			std::cout << " ";
	}

	std::cout << std::endl << "Leaves" << std::endl;
}

int main(void){
	std::srand(time(0));
	int sizes[3] = {2, 4, 2};
	double inputs[2] = {20, 20}; // Not poisonous
	Fruit* fruitSalad = new Fruit[SAMPLE_SIZE];
	PrintFruits(fruitSalad, SAMPLE_SIZE);

	NeuralNetwork<Fruit> network(sizes, 2);
	network.Learn(fruitSalad, SAMPLE_SIZE, 0.02);
	MeasureAccuracy(fruitSalad, SAMPLE_SIZE, network);
	std::cout << ((network.Classify(inputs)) == 0 ? "\033[41;1mPoisonous\033[0m" : "\033[42;1mSafe\033[0m") << std::endl;
	delete[] fruitSalad;
}