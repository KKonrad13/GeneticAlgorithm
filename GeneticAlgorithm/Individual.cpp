#include "Individual.h"
#include <cstdlib>

std::random_device Individual::rd;
std::uniform_real_distribution<double> Individual::randomProbability(0.0, 1.0);
std::uniform_int_distribution<int> Individual::randomGene(0, 1);

Individual::Individual()  {
	randomCrossoverPoint = std::uniform_int_distribution<int>(0, 0);
}

Individual::Individual(std::vector<int> solution) {
	randomCrossoverPoint = std::uniform_int_distribution<int>(0, solution.size() - 1);
	genome = solution;
}

Individual::Individual(int size) {
	randomCrossoverPoint = std::uniform_int_distribution<int>(0, size - 1);
	genome.resize(size);
	for (int i = 0; i < size; i++) {
		genome[i] = randomGene(rd);
	}
}

Individual::Individual(const Individual& other) {
	genome = other.genome;
}

Individual& Individual::operator=(const Individual& other) {
	genome = other.genome;
	return *this;
}

int Individual::fitness(const KnapsackProblem& problem) {
	return problem.genomeFitness(genome);
}

std::vector<int> Individual::getGenome() { 
	return genome; 
}

void Individual::mutate(double mutationProb) {
	for (int i = 0; i < genome.size(); i++) {
		if (getRandomProbability() < mutationProb) {
			if (genome[i] == 1) genome[i] = 0;
			else if (genome[i] == 0) genome[i] = 1;
		}
	}
}

double Individual::getRandomProbability() {
	return randomProbability(rd);
}

std::vector<Individual> Individual::crossover(const Individual &other, double crossoverProbality) {
	
	double probability = getRandomProbability();
	if (probability < crossoverProbality) {

		int crossoverPoint = randomCrossoverPoint(rd);

		std::vector<int> newGenome1(genome.size());
		std::vector<int> newGenome2(genome.size());

		for (int i = 0; i < crossoverPoint; i++) {
			newGenome1[i] = genome[i];
			newGenome2[i] = other.genome[i];
		}

		for (int i = crossoverPoint; i < genome.size(); i++) {
			newGenome1[i] = other.genome[i];
			newGenome2[i] = genome[i];
		}
		
		return { Individual(newGenome1), Individual(newGenome2) };
	}
	else
		return { Individual(genome), Individual(other.genome) };
}
