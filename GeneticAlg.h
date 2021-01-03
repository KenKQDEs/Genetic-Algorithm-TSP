#pragma once
#include <map>
#include <vector>
#include <functional>
#include <iostream>
#include <fstream>
#include <set>
#include <numeric>
#include <cmath>
#include "Random.h"
#include "Conversion.h"
#include "Experiment.h"
#include "BenchmarkFunctions.h"
#include "Mutation.h"
#include "Crossover.h"

#define MaxGenerations 3000
#define POP_SIZE 300
#define PM 1 //prob de a muta o solutie putin
#define PM1 0.051111 //probabilitatea de a muta o solutie mult
#define PCX 0.2 //prob crossover
#define MAX_GENS_NO_IMPROVEMENT 200
//#define PT 0.95



class GeneticAlg
{
public:
	GeneticAlg(Experiment ex) : ex(ex), CumulativeProportionsRoulette(POP_SIZE + 1), CumulativeProportionsRank(POP_SIZE+1), PopIntermediara(POP_SIZE + 1), Population(POP_SIZE + 1), writeOutput("Resz.txt")
	{

	}
	
private:
	std::ofstream writeOutput;
	std::vector<double> CumulativeProportionsRoulette;
	std::vector<double> CumulativeProportionsRank;
	std::vector<std::vector<size_t>> PopIntermediara;
	bool converges = false;
	size_t last_improvement = 0;
	Experiment ex;



	 std::vector<std::vector<size_t>> Population{ POP_SIZE };

public:
	long double Fitness(std::vector<size_t>& townSequence)
	{
		long double distanta = 0;
		for (int i = 0; i < townSequence.size() - 1; i++)
		{
			distanta += ex.distance[townSequence[i]][townSequence[i + 1]];
		}
		distanta += ex.distance[townSequence[townSequence.size() - 1]][townSequence[0]];
		return distanta;
	}

	std::vector<size_t> TournamentSelection(size_t k)
	{
		std::vector<std::vector<size_t>> solutiiAlese(k);
		for (int i = 0; i < k; i++)
		{
			size_t	poz = RandomHelpers::GetRandomFromRange<int>(0, POP_SIZE);
			solutiiAlese[i] = Population[poz];
		}
		std::sort(solutiiAlese.begin(), solutiiAlese.end(), [&solutiiAlese, this](std::vector<size_t> a, std::vector<size_t> b) -> bool
		{
				return Fitness(a) > Fitness(b);
		});
		return solutiiAlese[k - 1];
	}
	std::vector<size_t> RankSelection()
	{
		long double randomNum = RandomHelpers::GetRandomFromRange<long double>(0, 1);
		for (size_t i = 0; i < POP_SIZE; i++)
		{
			if (randomNum > CumulativeProportionsRank[i] && randomNum <= CumulativeProportionsRank[i + 1])
			{
				return PopIntermediara[i];
			}
		}
	}

	void CalculateCumulativeProbability()
	{
		//pentru rouletteWheel
		long double T = 0;
		std::vector<double> fValue(POP_SIZE); //fitness value
		std::vector<double> proportion(POP_SIZE + 1);

	
		for (int i = 0; i < POP_SIZE; i++)
		{
			fValue[i] = Fitness(Population[i]);
			T += fValue[i];
		}

		for (int i = 0; i < POP_SIZE; i++)
		{
			proportion[i] = fValue[i]/T;
		}

		CumulativeProportionsRoulette[0] = 0;
		for (int i = 0; i < POP_SIZE; i++)
		{
			CumulativeProportionsRoulette[i + 1] = CumulativeProportionsRoulette[i] + proportion[i];
			if (isnan(CumulativeProportionsRoulette[i]))
			{
				std::cout << "*****";
			}
		}


		/// pentru rank

		PopIntermediara = Population;
		std::sort(PopIntermediara.begin(), PopIntermediara.end(), [this](std::vector<size_t> a, std::vector<size_t> b) -> bool
		{
				return Fitness(a) > Fitness(b);
		});
		std::vector<long double> weight(POP_SIZE), cumulativeProbability(POP_SIZE + 1);
		size_t fitnessTotal = ((POP_SIZE+1) * (POP_SIZE)) / 2;
		for (size_t ii = 0; ii < PopIntermediara.size(); ii++)
		{
			weight[ii] = ((long double)ii+1) / fitnessTotal;
		}
		CumulativeProportionsRank[0] = 0;
		for (size_t ii = 0; ii < PopIntermediara.size(); ii++)
		{
			CumulativeProportionsRank[ii + 1] = CumulativeProportionsRank[ii] + weight[ii];
		}	
	}
	std::vector<size_t> GetParent()
	{
		long double p = RandomHelpers::GetRandomFromRange<long double>(0, 1);
		if (p < 0.5)
		{
			return RouletteWheel();
		}
		else
		//else if (p< 0.7)
		/*{
			return RankSelection();
		}else*/
		/*else
		{*/
			return TournamentSelection(2);
		//}
	}
	std::vector<size_t> RouletteWheel()
	{
		long double randomNum = RandomHelpers::GetRandomFromRange<long double>(0, 1);
		for (size_t i = 0; i < POP_SIZE; i++)
		{
			if ( randomNum > CumulativeProportionsRoulette[i] &&  randomNum <= CumulativeProportionsRoulette[i+1] )
			{
				return Population[i];
			}
		}
		
		throw("Bad stuff hapening");
	}
	std::vector<std::vector<size_t>> GenerateSelection()
	{
		
		long double avgFit = 0;
		for (auto& vec : Population)
		{
			avgFit += Fitness(vec);
		}
		avgFit /= POP_SIZE;

		std::vector<std::vector<size_t>> descendenti;
		descendenti.reserve(POP_SIZE);
		
		while (descendenti.size() < POP_SIZE)
		{
			std::vector<size_t> mother, father;
			mother = GetParent();
			father = GetParent();
			/*while (mother == father)
			{
				father = GetParent();
			}*/
			
			std::vector<size_t> fiu1, fiu2;
			if (RandomHelpers::GetRandomFromRange<double>(0, 1) <= PCX)
			{
				auto v = Crossover(mother, father);
				fiu1 = v.first;
				fiu2 = v.second;
			}
			else
			{
				continue;
			}

			//Mutate
			long double pm = PM1;
			if (Fitness(fiu1) < avgFit) pm = pm * 5;

			if (RandomHelpers::GetRandomFromRange<long double>(0, 1) <= pm)
			{
				Mutate(fiu1);
			}
			pm = PM1;
			if (Fitness(fiu2) < avgFit) pm = pm * 5;
			if (RandomHelpers::GetRandomFromRange<long double>(0, 1) <= pm)
			{
				Mutate(fiu2);
			}

			descendenti.push_back(fiu1);
			descendenti.push_back(fiu2);
		}

		descendenti.insert(descendenti.end(), Population.begin(), Population.end());


		std::sort(descendenti.begin(), descendenti.end(), [&descendenti, this](std::vector<size_t> a, std::vector<size_t> b) -> bool
		{
			return Fitness(a) > Fitness(b);
		});
		for (int i = 0; i < POP_SIZE; i++)
		{
			Mutate(Population[i]);
		}
		std::sort(descendenti.begin(), descendenti.end(), [&descendenti, this](std::vector<size_t> a, std::vector<size_t> b) -> bool
		{
				return Fitness(a) > Fitness(b);
		});

		descendenti = std::vector<std::vector<size_t>>(descendenti.begin() + POP_SIZE, descendenti.end());

		return descendenti;
	}
	


	void Mutate(std::vector<size_t>& first)
	{
	
			//Generate::PrintSolution(first);
			Mutation::mutate(first);
			//Generate::PrintSolution(first);
			

	}


	

	std::pair<std::vector<size_t>, std::vector<size_t>> Crossover(std::vector<size_t> first, std::vector<size_t> second)
	{
		return Crossover::Crossoverul(first, second);
	}
	long double CalculateDistance(std::vector<size_t> towns)
	{
		long double distance = 0;
		for (int i = 0; i < towns.size() - 1; i++)
		{
			distance += ex.distance[towns[i]][towns[i + 1]];
		}
		return distance;
	}
	std::vector<size_t> RunBasicGA()
	{

		size_t t = 0;

		std::vector<size_t> best = Population[0];
		//Population = RandomHelpers::GenerateRandomPopulation(POP_SIZE, ex.solution_size);
		Population = Generate::generatePopulation(ex.TownNumber);

		/*for (auto& vec : Population)
		{
			Generate::PrintSolution(vec);
		}*/


		long double minFitness = std::numeric_limits<long double>::max();
		while (t <= MaxGenerations && !converges)
		{
			t++;
			
			CalculateCumulativeProbability();
			/*long double minF = CalculateDistance(Population[0]);
			bool equal = true;
			for (int i = 1; i < POP_SIZE; i++)
			{
				if (minF != CalculateDistance(Population[i]))
				{
					equal = false;
					break;
				}
			}
			if (equal == true)
			{
				converges = true;
				continue;
			}*/
			std::vector<std::vector<size_t>> newPop = GenerateSelection();
			for (size_t i = 0; i < Population.size(); i++) /// update best 
			{
				long double temp = Fitness(Population[i]);
				if (temp < minFitness)
				{
					minFitness = temp;
					best = Population[i];
					last_improvement = t;
				}
			}
			Population = newPop;
			if(abs((int)(t-last_improvement) > MAX_GENS_NO_IMPROVEMENT))
				break;
		}
		return best;
	}
};

//lin 318 42029
