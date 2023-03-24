#include "GeneticAlgorithm.h"
#include "ERROR.h"
#include <ctime>
const int POPULATION_SIZE = 5000;
const int ITERATION_TIME_IN_MS = 500;
const double CROSSOVER_PROBABILITY = 0.4;
const double MUTATION_PROBABILITY = 0.2;

std::random_device GeneticAlgorithm::rd;

GeneticAlgorithm::GeneticAlgorithm(const KnapsackProblem& problem) {
	this->problem = problem;
	populationSize = POPULATION_SIZE;
	randomIndex = std::uniform_int_distribution<int>(0, populationSize - 1);
	crossoverProbability = CROSSOVER_PROBABILITY;
	mutationProbability = MUTATION_PROBABILITY;
	iterationDurationInMs = ITERATION_TIME_IN_MS;
}

int GeneticAlgorithm::setAlgorithmParameters(int popSize, double crossoverProb, double mutationProb, int iterDuration) {
	if (popSize <= 0) return WRONG_POPULATION_SIZE_ERROR;

	randomIndex = std::uniform_int_distribution<int>(0, popSize - 1);
	populationSize = popSize;

	if (crossoverProb < 0 || crossoverProb > 1) return WRONG_CROSSOVER_PROBABILITY_ERROR;
	crossoverProbability = crossoverProb;

	if (mutationProb < 0 || mutationProb > 1) return WRONG_MUTATION_PROBABILITY_ERROR;
	mutationProbability = mutationProb;

	if (iterDuration <= 0) return WRONG_ITERATION_TIME_ERROR;
	iterationDurationInMs = iterDuration;

	return SUCCESS_ERROR;
}

void GeneticAlgorithm::createPopulation(int genomeSize) {
	population.resize(populationSize);
	for (int i = 0; i < populationSize; i++) {

		population[i] = Individual(genomeSize);

		if (population[i].fitness(problem) > bestCurrentSolution.fitness(problem)) {
			bestCurrentSolution = population[i];
		}
	}
}

int GeneticAlgorithm::getRandomIndividualIndex() {
	return randomIndex(rd);
}

int GeneticAlgorithm::chooseParentIndex() {
	int randomIndividuals[2];
	randomIndividuals[0] = getRandomIndividualIndex();//we get 2 random individuals idexes and we choose the better one
	randomIndividuals[1] = getRandomIndividualIndex();

	int chosenIndex;
	if (population[randomIndividuals[0]].fitness(problem) > population[randomIndividuals[1]].fitness(problem)) {
		chosenIndex = randomIndividuals[0];
	}
	else chosenIndex = randomIndividuals[1];

	return chosenIndex;
}

void GeneticAlgorithm::updateBestIndividual(Individual& individual) {
	if (individual.fitness(problem) > bestCurrentSolution.fitness(problem)) {
		bestCurrentSolution = individual;
	}
}

Individual GeneticAlgorithm::evaluatePopulation() {
	createPopulation(problem.getNumberOfItems());
	std::vector<Individual> newPopulation(populationSize);

	int parentsIndexes[2];
	std::vector<Individual> childrenPair(2);
	double start = clock();
	double time = start;
	while (((time = clock()) - start) / (double)CLOCKS_PER_SEC * 1000 < iterationDurationInMs) {
		for (int i = 0; i < populationSize; i += 2) {
			if (i + 1 == populationSize) {
				//when population is an odd number
				newPopulation[i] = population[chooseParentIndex()];
				newPopulation[i].mutate(mutationProbability);
			}
			else {
				//choosing parents
				parentsIndexes[0] = chooseParentIndex();
				parentsIndexes[1] = chooseParentIndex();

				if (parentsIndexes[0] != parentsIndexes[1]) {
					//choosing children
					childrenPair = population[parentsIndexes[0]].crossover(population[parentsIndexes[1]], crossoverProbability);

					newPopulation[i] = childrenPair[0];
					newPopulation[i + 1] = childrenPair[1];

				}
				else {
					//when parents are the same
					newPopulation[i] = population[parentsIndexes[0]];
					newPopulation[i + 1] = population[parentsIndexes[1]];
				}

				newPopulation[i].mutate(mutationProbability);
				newPopulation[i + 1].mutate(mutationProbability);

				updateBestIndividual(newPopulation[i]);
				updateBestIndividual(newPopulation[i + 1]);
			}
			
		}

		population = newPopulation;
	}
	return bestCurrentSolution;
}

void GeneticAlgorithm::setProblem(KnapsackProblem& problem) {
	this->problem = problem;
}