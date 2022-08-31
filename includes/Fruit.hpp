#ifndef FRUIT_HPP
# define FRUIT_HPP
# include <random>

class Fruit{
public:
	Fruit();
	Fruit(double spots, double leaves, bool poison);
	virtual ~Fruit();

	bool isPoisonous();
	double* traits;
	double* expectedResult;
private:
	double ammountOfSpots;
	double lenOfLeaves;
	bool	poisonous;
};

#endif