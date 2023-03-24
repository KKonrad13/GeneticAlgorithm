#include "Individual.h"
#include <cstdlib>

std::random_device Individual::rd;
std::uniform_real_distribution<double> Individual::randomProbability(0.0, 1.0);
std::uniform_int_distribution<int> Individual::randomGene(0, 1);

Individual::Individual()  {
	randomCrossoverPoint = std::uniform_int_distribution<int>(0, 0);
}

Individual::Individual(std::vector<int>& solution) {
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

void Individual::resizeGenome(int size) {
	genome.resize(size);
	randomCrossoverPoint = std::uniform_int_distribution<int>(0, size);
}

void Individual::setGeneOnIndex(int gene, int index) {
	genome[index] = gene;
}

std::vector<Individual> Individual::crossover(const Individual &other, double crossoverProbality) {
	
	double probability = getRandomProbability();
	if (probability < crossoverProbality) {

		int crossoverPoint = randomCrossoverPoint(rd);

		Individual newIndividual1;
		Individual newIndividual2;

		newIndividual1.resizeGenome(genome.size());
		newIndividual2.resizeGenome(genome.size());

		for (int i = 0; i < crossoverPoint; i++) {
			newIndividual1.setGeneOnIndex(genome[i], i);
			newIndividual1.setGeneOnIndex(other.genome[i], i);
		}

		for (int i = crossoverPoint; i < genome.size(); i++) {
			newIndividual1.setGeneOnIndex(other.genome[i], i);
			newIndividual1.setGeneOnIndex(genome[i], i);
		}
		
		return { newIndividual1, newIndividual2 };
	}
	else
		return { *this, other };
}
