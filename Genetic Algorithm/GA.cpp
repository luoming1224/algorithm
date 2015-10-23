// GA.cpp : 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <ctime>


# define POPSIZE 50
# define GENESIZE 64
# define MAXGENS 1000
# define NVARS 3
#define tournamentSize 5
double uniformRate = 0.5;
double mutationRate = 0.015;
bool elitism = true;

double Random()
{
	double ran_numf=0.0;

#ifdef WIN32
	ran_numf = rand() / (double)(RAND_MAX+1);
#else
	ran_numf = rand() / (double)(RAND_MAX);
#endif

	return ran_numf;
}

int Round( double x )
{
	if (x >= 0 && x < 0.5)
	{
		return 0;
	}
	else if (x >= 0.5 && x <= 1)
	{
		return 1;
	}
}

char solution[GENESIZE] = {0};

typedef struct individual 
{
	char genes[GENESIZE];
	int fitness;
	individual& operator=(const individual& tmp)
	{
		for (int j = 0; j < GENESIZE; j++)
		{
			genes[j] = tmp.genes[j];
		}
		fitness = tmp.fitness;
		return *this;
	}
}Individual;

struct individual population[POPSIZE];

void initialize();
int evaluate(Individual tindividual);
void selector();
Individual crossover(Individual indiv1, Individual indiv2);
void mutate(Individual& indiv);
int getIndividualFitness(Individual tindividual);
Individual getPopulationFitness(Individual* individuals, int nSize);
Individual tournamentSelection(Individual* pop);
void evolvePopulation(Individual* individuals);

void initialize()
{
	std::string strsolution = "1111000000000000000000000000000000000000000000000000000000001111";
	int size = strsolution.length();
	for (int i = 0; i < size; i++)
	{
		solution[i] = (char)(strsolution[i] - '0');
	}

	for(int j = 0; j < POPSIZE; j++)
	{
		for (int i = 0; i < GENESIZE; i++) {
			char gene = (char) Round(Random());
			population[j].genes[i] = gene;
		}
		population[j].fitness = evaluate(population[j]);
	}
}

int evaluate(Individual tindividual)
{
	int fitness = 0;
	for (int i = 0; i < GENESIZE; i++) {
		if (tindividual.genes[i] == solution[i]) {
			fitness++;
		}
	}
	return fitness;
}

int getIndividualFitness(Individual tindividual)
{
	if (tindividual.fitness == 0)
	{
		tindividual.fitness = evaluate(tindividual);
	}
	return tindividual.fitness;
}

Individual getPopulationFitness(Individual* individuals, int nSize)
{
	Individual fittest = individuals[0];
	int nFitness = getIndividualFitness(fittest);
	// Loop through individuals to find fittest
	for (int i = 1; i < nSize; i++) 
	{	
		int ntmpFit = getIndividualFitness(individuals[i]);
		if (nFitness <= ntmpFit)
		{
			fittest = individuals[i];
			nFitness = ntmpFit;
		}
	}
	return fittest;
}

Individual crossover(Individual indiv1, Individual indiv2)
{
	Individual newSol;
	
	for (int i = 0; i < GENESIZE; i++) {
		
		if (Random() <= uniformRate) 
		{
			newSol.genes[i] = indiv1.genes[i];
		} 
		else 
		{
			newSol.genes[i] = indiv2.genes[i];
		}
	}
	newSol.fitness = 0;			//
	return newSol;
}

void mutate(Individual& indiv)
{
	for (int i = 0; i < GENESIZE; i++) {
		if (Random() <= mutationRate) {
			
			char gene = (char) Round(Random());
			indiv.genes[i] = gene;
			indiv.fitness = 0;		//突变后fitness需要重新计算
		}
	}
}

Individual tournamentSelection(Individual* pop)
{
	Individual tournament[tournamentSize];
	for (int i = 0; i < tournamentSize; i++)
	{
		int randomId = (int)(Random()*POPSIZE);
		tournament[i] = pop[randomId];
	}
	Individual fittest = getPopulationFitness(tournament, tournamentSize);
	return fittest;
}

void evolvePopulation(Individual* individuals)
{
	Individual newpopulation[POPSIZE];
	int elitismOffset = 0;
	if (elitism)
	{
		newpopulation[0] = getPopulationFitness(individuals, POPSIZE);
		elitismOffset = 1;
	}

	for (int i = elitismOffset; i < POPSIZE; i++)
	{
		Individual indiv1 = tournamentSelection(individuals);
		Individual indiv2 = tournamentSelection(individuals);
		Individual newIndiv = crossover(indiv1, indiv2);
		newpopulation[i] = newIndiv;
	}

	for (int i = elitismOffset; i < POPSIZE; i++)
	{
		mutate(newpopulation[i]);
	}

	for (int i = 0; i < POPSIZE; i++)
	{
		individuals[i] = newpopulation[i];
	}
}


int main()
{
	srand((unsigned)time(0));

	initialize();

	int generationCount = 0;

	Individual FitIndiv = getPopulationFitness(population, POPSIZE);
	int nFitness = getIndividualFitness(FitIndiv);
	while( nFitness < GENESIZE)
	{
		generationCount++;
		printf("Generation: %d  Fittest: %d\n", generationCount , nFitness);
		evolvePopulation(population);
		FitIndiv = getPopulationFitness(population, POPSIZE);
		nFitness = getIndividualFitness(FitIndiv);
	}

	printf("Solution found!\n");
	printf("Generation: %d, nFitness: %d\n", generationCount, nFitness);

	for (int i = 0; i < GENESIZE; i++)
	{
		printf("%d",FitIndiv.genes[i]);
	}
	printf("\n");

	system("pause");
	return 0;
}

