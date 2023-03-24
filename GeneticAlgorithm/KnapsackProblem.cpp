#include "KnapsackProblem.h"
#include "ERROR.h"
#include <fstream>
#include <sstream>

const int CORRECT_NUMBER_OF_INTS_IN_LINE = 3;

KnapsackProblem::KnapsackProblem() {
	knapsackSize = 0;
}

int KnapsackProblem::setProblemParameters(int size, std::vector<Item>& itemsVector) {
	if (size <= 0) return WRONG_KNAPSACK_SIZE_ERROR;
	if (itemsVector.size() == 0) return EMPTY_VECTOR_ERROR;
	knapsackSize = size;
	this->items = itemsVector;
	return SUCCESS_ERROR;
}

int KnapsackProblem::accessProblemFromFile(std::string fileName) {
	std::ifstream file(fileName);
	if (file.is_open()) {
		std::string line;

		std::getline(file, line);
		
		try {
			knapsackSize = stoi(line);
		}
		catch (const std::invalid_argument& ia) {
			return WRONG_ARGUMENT_TYPE_IN_FILE_ERROR;
		}
		if (knapsackSize < 0) return WRONG_KNAPSACK_SIZE_ERROR;

		std::getline(file, line);
		int numberOfItems;
		try {
			numberOfItems = stoi(line);
		}
		catch(const std::invalid_argument& ia) {
			return WRONG_ARGUMENT_TYPE_IN_FILE_ERROR;
		}
		if (numberOfItems < 0) return WRONG_NUMBER_OF_ITEMS_ERROR;

		items.resize(numberOfItems);

		for (int i = 0; i < numberOfItems; i++) {
			std::string stringIndex, stringValue, stringSize;
			int intIndex, intValue, intSize;
				std::getline(file, line);
				std::stringstream ss(line);
				ss >> stringIndex >> stringValue >> stringSize;
				try {
					intIndex = stoi(stringIndex);
					intValue = stoi(stringValue);
					intSize = stoi(stringSize);
					if (intIndex < 0) return WRONG_INDEX_FORMAT_ERROR;
					if (intValue < 0) return WRONG_ITEM_VALUE_ERROR;
					if (intSize < 0) return WRONG_ITEM_SIZE_ERROR;

					items[intIndex].value = intValue;
					items[intIndex].size = intSize;
				}
				catch (const std::invalid_argument& ia) {
					return WRONG_ARGUMENT_TYPE_IN_FILE_ERROR;
				}
		}

		file.close();
		return SUCCESS_ERROR;
	}

	return FILE_NOT_OPEN_ERROR;
}

int KnapsackProblem::genomeFitness(std::vector<int>& genome) const{
	if (genome.size() != items.size()) return WRONG_GENOME_SIZE_ERROR;

	int individualFitness = 0;
	int individualSize = 0;
	for (int i = 0; i < genome.size(); i++) {
		if (genome[i] == 1) {
			individualFitness += items[i].value;
			individualSize += items[i].size;
		}
	}

	if (individualSize > knapsackSize) individualFitness = 0;
	return individualFitness;
}

int KnapsackProblem::getKnapsackSize() { return knapsackSize; }
int KnapsackProblem::getNumberOfItems() { return (int)items.size(); }