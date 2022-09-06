#include "nn.hpp"
#include "Fruit.hpp"

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

int main(void){
	std::srand(std::time(nullptr));
	int sizes[3] = {2, 3, 2};
	double inputs[2] = {0, 1};
	Fruit* fruitSalad = new Fruit[100];
	PrintFruits(fruitSalad, 100);

	NeuralNetwork<Fruit> network(sizes, 2);
	network.Learn(fruitSalad, 100, 0.02);
	std::cout << network.Classify(inputs) << std::endl;
	delete[] fruitSalad;
}