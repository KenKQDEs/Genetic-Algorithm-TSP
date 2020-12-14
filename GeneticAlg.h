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



class GeneticAlg
{
public:
	GeneticAlg(Experiment ex) : ex(ex), CumulativeProportions(POP_SIZE + 1), Population(POP_SIZE + 1), fff("Resz.txt")
	{

	}
	
private:
	std::ofstream writeOutput;
	std::vector<double> CumulativeProportions;
	bool converges = false;
	Experiment ex;



	 std::vector<std::vector<char>> Population{ POP_SIZE };

public:
	long double Fitness(/**/)
	{
		//implement
	}

	void CalculateCumulativeProbabilityAndGenerationMinMax()
	{

		long double T = 0;
		std::vector<double> fValue(POP_SIZE); //fitness value
		std::vector<double> proportion(POP_SIZE + 1);

	
		for (int i = 0; i < POP_SIZE; i++)
		{
			fValue[i] = Fitness();
			T += fValue[i];
		}

		for (int i = 0; i < POP_SIZE; i++)
		{
			proportion[i] = fValue[i]/T;
		}

		CumulativeProportions[0] = 0;
		for (int i = 0; i < POP_SIZE; i++)
		{
			CumulativeProportions[i + 1] = CumulativeProportions[i] + proportion[i];
			if (isnan(CumulativeProportions[i]))
			{
				std::cout << "";
			}
		}
	}
	std::vector<char> GetParent()
	{
		return RouletteWheel();
	}
	std::vector<char> RouletteWheel()
	{
		long double randomNum = RandomHelpers::GetRandomFromRange<long double>(0, 1);
		for (size_t i = 0; i < POP_SIZE; i++)
		{
			if ( randomNum > CumulativeProportions[i] &&  randomNum <= CumulativeProportions[i+1] )
			{
				return Population[i];
			}
		}
		
		throw("Bad stuff hapening");
	}
	std::vector<std::vector<char>> GenerateSelection()
	{
		std::vector<std::vector<char>> descendenti;
		descendenti.reserve(POP_SIZE);
	
		
		while (descendenti.size() < POP_SIZE)
		{
			std::vector<char> mother, father;
			mother = GetParent();
			father = GetParent();
			while (mother == father)
			{
				father = GetParent();
			}
			std::vector<char> fiu1, fiu2;
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


		std::sort(descendenti.begin(), descendenti.end(), [&descendenti, this](std::vector<char> a, std::vector<char> b) -> bool
		{
			return Fitness(ConvertBack(a, d[ex.function], ex.comp_size)) < Fitness(ConvertBack(b, d[ex.function], ex.comp_size));
		});

		descendenti = std::vector<std::vector<char>>(descendenti.begin() + POP_SIZE, descendenti.end());

		for (int i=0; i< POP_SIZE / 2 ; i++)
		{
			Mutate(PM1, descendenti[i]);
		}
		return descendenti;
	}
	

	void MutateSlightly(double pm, std::vector<char>& first, std::vector<char>& second)
	{
		if (RandomHelpers::GetRandomFromRange<long double>(0, 1) > 0.5)
		{
		
		
				
		}
		else
		{

		}
		
	}
	void Mutate(double pm, std::vector<char>& first)
	{
		if (RandomHelpers::GetRandomFromRange<long double>(0, 1) > 0.5)
		{
		
			
				
		}
		else
		{
			
		}
		
	}


	

	std::pair<std::vector<char>, std::vector<char>> Crossover(double pcx, std::vector<char> first, std::vector<char> second)
	{
		
	}

	std::vector<char> RunBasicGA()
	{

		size_t t = 0;

		std::vector<char> best = Population[0];
		Population = RandomHelpers::GenerateRandomPopulation(POP_SIZE, ex.solution_size);
		long double minVal = std::numeric_limits<long double>::max();
		while (t <= MaxGenerations && !converges)
		{
			t++;
			
			CalculateCumulativeProbabilityAndGenerationMinMax();
			if (minF == maxF)
				return best;
			auto newPop = GenerateSelection();
			for (size_t i = 0; i < Population.size(); i++) /// update best 
			{
				long double temp = eval;
				if (temp < minVal)
				{
					minVal = temp;
					best = Population[i];
				}
			}
			Population = newPop;
			
		}
		return best;
	}
};



