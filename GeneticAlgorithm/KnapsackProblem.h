#pragma once
#include <string>
#include <vector>
class KnapsackProblem
{
public:
	KnapsackProblem();
	struct Item { int value; int size; };
	int setProblemParameters(int size, std::vector<Item>& itemsVector);
	int accessProblemFromFile(std::string fileName);
	int genomeFitness(std::vector<int>& genome) const;

	int getKnapsackSize();
	int getNumberOfItems();
private:
	int knapsackSize;
	std::vector<Item> items;
};

