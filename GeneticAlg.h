#pragma once
#include <map>
#include <vector>
#include <functional>
#include <iostream>
#include <fstream>
#include <set>
#include "Random.h"
#include "Conversion.h"
#include "Experiment.h"
#include "BenchmarkFunctions.h"

#define MaxGenerations 1000
#define POP_SIZE 100
#define PM 1 //prob de a muta o solutie putin
#define PM1 0.01 //probabilitatea de a muta o solutie mult
#define PCX 0.2 //prob crossover
#define PT 0.95



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
	Experiment ex;



	 std::vector<std::vector<size_t>> Population{ POP_SIZE };

public:
	long double Fitness(std::vector<size_t>& townSequence)
	{
		long long distanta = 0;
		for (int i = 0; i < townSequence.size() - 1; i++)
		{
			distanta += ex.distance[i][i + 1];
		}
		return (long double)1 / distanta;
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
				return Fitness(a) < Fitness(b);
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
				std::cout << "";
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
			weight[ii] = (ii+1) / fitnessTotal;
		}
		CumulativeProportionsRank[0] = 0;
		for (size_t ii = 0; ii < PopIntermediara.size(); ii++)
		{
			CumulativeProportionsRank[ii + 1] = CumulativeProportionsRank[ii] + weight[ii];
		}
	}
	std::vector<size_t> GetParent()
	{
		return RouletteWheel();
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
		std::vector<std::vector<size_t>> descendenti;
		descendenti.reserve(POP_SIZE);
	
		
		while (descendenti.size() < POP_SIZE)
		{
			std::vector<size_t> mother, father;
			mother = GetParent();
			father = GetParent();
			while (mother == father)
			{
				father = GetParent();
			}
			std::vector<size_t> fiu1, fiu2;
			if (RandomHelpers::GetRandomFromRange<double>(0, 1) <= PCX)
			{
				auto v = Crossover(PCX, mother, father);
				fiu1 = v.first;
				fiu2 = v.second;
			}
			else
				continue;

			//Mutate
			if (RandomHelpers::GetRandomFromRange<long double>(0, 1) <= PM)
			{
				MutateSlightly(PM, fiu1, fiu2);
			}
			else
			{
				Mutate(PM, fiu1);
				Mutate(PM, fiu2);
			}

			descendenti.push_back(fiu1);
			descendenti.push_back(fiu2);
		}

		descendenti.insert(descendenti.end(), Population.begin(), Population.end());


		std::sort(descendenti.begin(), descendenti.end(), [&descendenti, this](std::vector<size_t> a, std::vector<size_t> b) -> bool
		{
			return Fitness(a) < Fitness(b);
		});

		descendenti = std::vector<std::vector<size_t>>(descendenti.begin() + POP_SIZE, descendenti.end());

		for (int i=0; i< POP_SIZE / 2 ; i++)
		{
			Mutate(PM1, descendenti[i]);
		}
		return descendenti;
	}
	

	void MutateSlightly(double pm, std::vector<size_t>& first, std::vector<size_t>& second)
	{
		if (RandomHelpers::GetRandomFromRange<long double>(0, 1) > 0.5)
		{
		
		
				
		}
		else
		{

		}
		
	}
	void Mutate(double pm, std::vector<size_t>& first)
	{
		if (RandomHelpers::GetRandomFromRange<long double>(0, 1) > 0.5)
		{
		
			
				
		}
		else
		{
			
		}
		
	}


	

	std::pair<std::vector<size_t>, std::vector<size_t>> Crossover(double pcx, std::vector<size_t> first, std::vector<size_t> second)
	{
		return {};
	}

	std::vector<size_t> RunBasicGA()
	{

		size_t t = 0;

		std::vector<size_t> best = Population[0];
		//Population = RandomHelpers::GenerateRandomPopulation(POP_SIZE, ex.solution_size);
		long double maxFitness = std::numeric_limits<long double>::max();
		while (t <= MaxGenerations && !converges)
		{
			t++;
			
			CalculateCumulativeProbability();

			auto newPop = GenerateSelection();
			for (size_t i = 0; i < Population.size(); i++) /// update best 
			{
				long double temp = Fitness(Population[i]);
				if (temp > maxFitness)
				{
					maxFitness = temp;
					best = Population[i];
				}
			}
			Population = newPop;
			
		}
		return best;
	}
};


