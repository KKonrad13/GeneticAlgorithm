#include "GeneticAlgorithm.h"
#include "ERROR.h"
#include <iostream>

void evaluateProblemFromFile(std::string fileName, std::vector<int> optimal) {
	KnapsackProblem problem;
	int fileAccessSuccessful = problem.accessProblemFromFile(fileName);
	if (fileAccessSuccessful == SUCCESS_ERROR) {
		std::cout << fileName;
		std::cout << "\n==============================================\n";

		GeneticAlgorithm ga(problem);

		Individual bestIndividual(ga.evaluatePopulation());
		bestIndividual = ga.evaluatePopulation();
		std::vector<int> genome = bestIndividual.getGenome();
		for (int i = 0; i < genome.size(); i++) {
			std::cout << genome[i];
		}
		std::cout << "\n==============================================\n";
		//to check a specific one
		std::cout << "\n" << bestIndividual.fitness(problem);
		std::cout << std::endl;
		int otherGenomeFitness = problem.genomeFitness(optimal);
		if (otherGenomeFitness != WRONG_GENOME_SIZE_ERROR) {
			std::cout << otherGenomeFitness;
		}
		else {
			std::cout << "WRONG_GENOME_SIZE_ERROR\n";
		}
		std::cout << "\n==============================================\n";

	}
	else if (fileAccessSuccessful == WRONG_KNAPSACK_SIZE_ERROR) {
		std::cout << "WRONG_KNAPSACK_SIZE_ERROR\n";
	}
	else if (fileAccessSuccessful == WRONG_NUMBER_OF_ITEMS_ERROR) {
		std::cout << "WRONG_NUMBER_OF_ITEMS_ERROR\n";
	}
	else if (fileAccessSuccessful == WRONG_ITEMS_FORMAT_ERROR) {
		std::cout << "WRONG_ITEMS_FORMAT_ERROR\n";
	}
	else if (fileAccessSuccessful == FILE_NOT_OPEN_ERROR) {
		std::cout << "FILE_NOT_OPEN_ERROR\n";
	}
	else if (fileAccessSuccessful == WRONG_INDEX_FORMAT_ERROR) {
		std::cout << "WRONG_INDEX_FORMAT_ERROR\n";
	}
	else if (fileAccessSuccessful == WRONG_ITEM_VALUE_ERROR) {
		std::cout << "WRONG_ITEM_VALUE_ERROR\n";
	}
	else if (fileAccessSuccessful == WRONG_ITEM_SIZE_ERROR) {
		std::cout << "WRONG_ITEM_SIZE_ERROR\n";
	}
	else if (fileAccessSuccessful == WRONG_ARGUMENT_TYPE_IN_FILE_ERROR) {
		std::cout << "WRONG_ARGUMENT_TYPE_IN_FILE\n";
	}
	else {
		std::cout << "UNKNOWN_ERROR\n";
	}
}

int validateItems(std::vector<KnapsackProblem::Item> items) {
	for (int i = 0; i < items.size(); i++) {
		if (items[i].value < 0) return WRONG_ITEM_VALUE_ERROR;
		if (items[i].size < 0) return WRONG_ITEM_SIZE_ERROR;
	}
	return SUCCESS_ERROR;
}

void evaluateProblemWithParameters
(int popSize, double crossoverProb, double mutationProb, int iterDuration, int knapsackSize, std::vector<KnapsackProblem::Item> items, std::vector<int> optimal) {
	int validItems = validateItems(items);
	if (validItems == SUCCESS_ERROR) {
		KnapsackProblem problem;
		int settingProblem = problem.setProblemParameters(knapsackSize, items);

		if (settingProblem == SUCCESS_ERROR) {
			std::cout << "METHOD WITH PARAMETERS\n";
			std::cout << "\n==============================================\n";

			GeneticAlgorithm ga(problem);

			int settingAlgorythmParameters = ga.setAlgorithmParameters(popSize, crossoverProb, mutationProb, iterDuration);

			if (settingAlgorythmParameters == SUCCESS_ERROR) {
				Individual bestIndividual;
				bestIndividual = ga.evaluatePopulation();
				std::vector<int> genome = bestIndividual.getGenome();
				for (int i = 0; i < genome.size(); i++) {
					std::cout << genome[i];
				}
				std::cout << "\n==============================================\n";
				//to check a specific one
				std::cout << "\n" << bestIndividual.fitness(problem);
				std::cout << std::endl;
				int otherGenomeFitness = problem.genomeFitness(optimal);
				if (otherGenomeFitness != WRONG_GENOME_SIZE_ERROR) {
					std::cout << otherGenomeFitness;
				}
				else {
					std::cout << "WRONG_GENOME_SIZE_ERROR\n";
				}
				std::cout << "\n==============================================\n";
			}
			else if (settingAlgorythmParameters == WRONG_POPULATION_SIZE_ERROR) {
				std::cout << "WRONG_POPULATION_SIZE_ERROR\n";
			}
			else if (settingAlgorythmParameters == WRONG_CROSSOVER_PROBABILITY_ERROR) {
				std::cout << "WRONG_CROSSOVER_PROBABILITY_ERROR\n";
			}
			else if (settingAlgorythmParameters == WRONG_MUTATION_PROBABILITY_ERROR) {
				std::cout << "WRONG_MUTATION_PROBABILITY_ERROR\n";
			}
			else if (settingAlgorythmParameters == WRONG_ITERATION_TIME_ERROR) {
				std::cout << "WRONG_ITERATION_TIME_ERROR\n";
			}
			else {
				std::cout << "UNKNOWN_ERROR\n";
			}

		}
		else if (settingProblem == WRONG_KNAPSACK_SIZE_ERROR) {
			std::cout << "WRONG_KNAPSACK_SIZE_ERROR\n";
		}
		else if (settingProblem == EMPTY_VECTOR_ERROR) {
			std::cout << "EMPTY_VECTOR_ERROR\n";
		}
		else {
			std::cout << "UNKNOWN_ERROR\n";
		}
	}
	else if (validItems == WRONG_ITEM_VALUE_ERROR) {
		std::cout << "WRONG_ITEM_VALUE_ERROR\n";
	}
	else if (validItems == WRONG_ITEM_SIZE_ERROR) {
		std::cout << "WRONG_ITEM_SIZE_ERROR\n";
	}
	else {
		std::cout << "UNKNOWN_ERROR\n";
	}

}



int main() {
	std::vector<int> optimal1 = { 1, 0, 0, 1};
	std::vector<int> optimal2 = { 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1 };
	evaluateProblemFromFile("problem1.txt", optimal1);
	evaluateProblemFromFile("problem2.txt", optimal2);
	evaluateProblemFromFile("problem3.txt", optimal1);

	std::vector<KnapsackProblem::Item> problem1(4);
	problem1[0].value = 2;
	problem1[0].size = 3;
	problem1[1].value = 3;
	problem1[1].size = 4;
	problem1[2].value = 1;
	problem1[2].size = 6;
	problem1[3].value = 4;
	problem1[3].size = 5;

	evaluateProblemWithParameters(5000, 0.3, 0.15, 500, 8, problem1, optimal1);

	return 0;
}