#pragma once
#include <random>
#include "Individual.h"
#include "KnapsackProblem.h"

class GeneticAlgorithm
{
public:
	GeneticAlgorithm(const KnapsackProblem& problem);

	int setAlgorithmParameters(int popSize, double crossoverProb, double mutationProb, int iterDuration);

	int getRandomIndividualIndex();
	void createPopulation(int genomeSize);
	int chooseParentIndex();
	void updateBestIndividual(Individual& individual);
	Individual evaluatePopulation();

	void setProblem(KnapsackProblem& problem);

private:
	int populationSize;
	double crossoverProbability;
	double mutationProbability;
	int iterationDurationInMs;
	Individual bestCurrentSolution;
	KnapsackProblem problem;
	std::vector<Individual> population;
	static std::random_device rd;
	std::uniform_int_distribution<int> randomIndex;
};

