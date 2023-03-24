#pragma once
#include "KnapsackProblem.h"
#include <random>
#include <vector>
class Individual 
{
public:
	Individual();
	Individual(int size);
	Individual(std::vector<int> solution);
	Individual(const Individual& other);

	Individual& operator=(const Individual& other);

	int fitness(const KnapsackProblem& problem);
	void mutate(double mutationProb);
	double getRandomProbability();
	std::vector<Individual> crossover(const Individual& other, double crossoverProbality);
	std::vector<int> getGenome();
private:
	std::vector<int> genome;
	static std::random_device rd;
	static std::uniform_real_distribution<double> randomProbability;
	std::uniform_int_distribution<int> randomCrossoverPoint;
	static std::uniform_int_distribution<int> randomGene;
};



