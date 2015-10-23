// GA.cpp : 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <ctime>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;

# define POPSIZE 50
# define GENESIZE 64
# define MAXGENS 1000
# define NVARS 3
double uniformRate = 0.5;
double mutationRate = 0.015;
//int tournamentSize = 5;
#define tournamentSize 5
#define NUMOFCITY 20
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

int roundd( double x )
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

struct City 
{
	int x;
	int y;
	City(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	double distanceTo(City city)
	{
		int xDistance = abs(x - city.x);
		int yDistance = abs(y - city.y);
		double distance = sqrt( (float)((xDistance*xDistance) + (yDistance*yDistance)) );
		return distance;
	}

	bool operator==(const City& tmp)
	{
		if (x == tmp.x && y == tmp.y)
		{
			return true;
		}
		else
			return false;
	}
};

typedef struct individual 
{
	vector<City> tour;
	double fitness;
	int distance;
	individual& operator=(const individual& tmp)
	{
		/*
		for (int j = 0; j < GENESIZE; j++)
				{
					genes[j] = tmp.genes[j];
				}*/
		tour.clear();
		for (int i = 0; i < NUMOFCITY; i++)
		{
			tour.push_back(tmp.tour[i]);
		}
		fitness = tmp.fitness;
		distance = tmp.distance;
		return *this;
	}

	int evaluate()
	{
		if (distance == 0)
		{
			double tourDistance = 0;
			for (int cityIndex = 0; cityIndex < NUMOFCITY; cityIndex++)
			{
				City fromCity = tour[cityIndex];
				City destinationCity(0,0);
				if (cityIndex+1 < NUMOFCITY)
				{
					destinationCity = tour[cityIndex+1];
				}
				else
				{
					destinationCity = tour[0];
				}
				tourDistance += fromCity.distanceTo(destinationCity);
			}
			distance = (int)tourDistance;
		}
		return distance;
	}

	double getFitness()
	{
		if (fitness == 0)
		{
			fitness = 1/(double)evaluate();
		}
		return fitness;
	}
}Individual;

struct individual population[POPSIZE];

void initialize();
double evaluate(individual tindividual);
void selector();
Individual crossover(Individual indiv1, Individual indiv2);
void mutate(Individual& indiv);
double getIndividualFitness(individual tindividual);
Individual getPopulationFitness(individual* individuals, int nSize);
Individual tournamentSelection(Individual* pop);
void evolvePopulation(Individual* individuals);

void initialize()
{
	individual tmp;
	tmp.tour.push_back(City(60, 200));
	tmp.tour.push_back(City(180, 200));
	tmp.tour.push_back(City(80, 180));
	tmp.tour.push_back(City(140, 180));
	tmp.tour.push_back(City(20, 160));
	tmp.tour.push_back(City(100, 160));
	tmp.tour.push_back(City(200, 160));
	tmp.tour.push_back(City(140, 140));
	tmp.tour.push_back(City(40, 120));
	tmp.tour.push_back(City(100, 120));
	tmp.tour.push_back(City(180, 100));
	tmp.tour.push_back(City(60, 80));
	tmp.tour.push_back(City(120, 80));
	tmp.tour.push_back(City(180, 60));
	tmp.tour.push_back(City(20, 40));
	tmp.tour.push_back(City(100, 40));
	tmp.tour.push_back(City(200, 40));
	tmp.tour.push_back(City(20, 20));
	tmp.tour.push_back(City(60, 20));
	tmp.tour.push_back(City(160, 20));

	tmp.fitness = 0.0;
	tmp.distance = 0;

	for(int j = 0; j < POPSIZE; j++)
	{
		individual init = tmp;
		random_shuffle(init.tour.begin(), init.tour.end());
		population[j] = init;
		population[j].fitness = 0.0;
		population[j].distance = 0;
//		population[j].fitness = population[j].getFitness();
	}
}
/*
double evaluate(individual tindividual)
{
	if (tindividual.distance == 0)
	{
		double tourDistance = 0;
		for (int cityIndex = 0; cityIndex < NUMOFCITY; cityIndex++)
		{
			City fromCity = tindividual.tour[cityIndex];
			City destinationCity(0,0);
			if (cityIndex+1 < NUMOFCITY)
			{
				destinationCity = tindividual.tour[cityIndex+1];
			}
			else
			{
				destinationCity = tindividual.tour[0];
			}
			tourDistance += fromCity.distanceTo(destinationCity);
		}
		tindividual.distance = tourDistance;
	}
	return tindividual.distance;
}

double getIndividualFitness(individual tindividual)
{
	if (tindividual.fitness == 0)
	{
		tindividual.fitness = 1/(double)evaluate(tindividual);
	}
	return tindividual.fitness;
}
*/
individual getPopulationFitness(individual* individuals, int nSize)
{
//	individual fittest = individuals[0];
	int index = 0;
	double nFitness = individuals[index].getFitness();
	// Loop through individuals to find fittest
	for (int i = 1; i < nSize; i++) 
	{	
		double ntmpFit = individuals[i].getFitness();
		if (nFitness <= ntmpFit)
		{
//			fittest = individuals[i];
			index = i;
			nFitness = ntmpFit;
		}
	}
	individual fittest = individuals[index];
	return fittest;
}

individual crossover(individual indiv1, individual indiv2)
{
	individual newSol;

	int startPos = (int)(Random()*NUMOFCITY);
	int endPos = (int)(Random()*NUMOFCITY);
	if (startPos > endPos)
	{
		int tmp = startPos;
		startPos = endPos;
		endPos = tmp;
	}

	int index2 = 0;
	for (int i = 0; i < NUMOFCITY; i++)
	{
		if (i>startPos && i < endPos)
		{
			newSol.tour.push_back(indiv1.tour[i]);
		}
		else
		{
			for (int j = index2; j < NUMOFCITY; j++)
			{
				bool bflag = true;
				for (int k = startPos+1; k < endPos; k++)
				{
					/*if (indiv1.tour[k].x == indiv2.tour[j].x && indiv1.tour[k].y == indiv2.tour[j].y)*/
					if (indiv1.tour[k] == indiv2.tour[j])
					{
						index2++;
						bflag = false;
						break;
					}
				}
				if (bflag)
				{
					newSol.tour.push_back(indiv2.tour[index2]);
					index2++;
					break;
				}
			}
			
		}
	}
	newSol.fitness = 0.0;			//
	newSol.distance = 0;
	return newSol;
}

void mutate(individual& indiv)
{
	for (int i = 0; i < NUMOFCITY; i++) {
		if (Random() <= mutationRate) {

			int tourPos2 = (int)(Random()*NUMOFCITY);
			City city1 = indiv.tour[i];
			City city2 = indiv.tour[tourPos2];
			indiv.tour[i] = city2;
			indiv.tour[tourPos2] = city1;
			indiv.fitness = 0.0;		//突变后fitness需要重新计算
			indiv.distance = 0;
		}
	}
}

individual tournamentSelection(individual* pop)
{
	individual tournament[tournamentSize];
	for (int i = 0; i < tournamentSize; i++)
	{
		int randomId = (int)(Random()*POPSIZE);
		tournament[i] = pop[randomId];
	}
	individual fittest = getPopulationFitness(tournament, tournamentSize);
	return fittest;
}

void evolvePopulation(individual* individuals)
{
	individual newpopulation[POPSIZE];
	int elitismOffset = 0;
	if (elitism)
	{
		newpopulation[0] = getPopulationFitness(individuals, POPSIZE);
		elitismOffset = 1;
	}

	for (int i = elitismOffset; i < POPSIZE; i++)
	{
		individual indiv1 = tournamentSelection(individuals);
		individual indiv2 = tournamentSelection(individuals);
		individual newIndiv = crossover(indiv1, indiv2);
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
	individual FitIndiv = getPopulationFitness(population, POPSIZE);
	printf("Initial distance: %d\n", FitIndiv.evaluate());

	for (int i = 0; i <200; i++)
	{
		evolvePopulation(population);
		FitIndiv = getPopulationFitness(population, POPSIZE);
		printf("calculation distance: %d\n", FitIndiv.evaluate());
	}
	evolvePopulation(population);
	FitIndiv = getPopulationFitness(population, POPSIZE);
	
	printf("Finished!\n");
	printf("Finished distance: %d\n", FitIndiv.evaluate());
	for (int i = 0; i < NUMOFCITY; i++)
	{
		printf("%d,%d | ", FitIndiv.tour[i].x, FitIndiv.tour[i].y);
	}
	printf("\n");


	system("pause");
	return 0;
}

