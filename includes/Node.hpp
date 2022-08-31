#ifndef NODE_HPP
# define NODE_HPP

class Node {
public:
	Node();
	Node(double threshold);
	virtual ~Node(){};

	void tryActivate(double weightedInput);
	double isActive();
private:
	double activationThreshold;
	double activationStatus;
};

#endif