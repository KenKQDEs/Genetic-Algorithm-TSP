#pragma once
#include <random>
#include <iostream>
class Generate
{public:
	static std::random_device rd;
	static std::mt19937 Generator;


	int Rand(size_t a,size_t b)
	{
		static std::uniform_int_distribution<>distr(a, b);
		int Number = (int)distr(Generator);
		return Number;
	}
	//initial am gresit putin si am facut generator de random intre 0 si numberPopulation si mda
	std::vector<size_t>Generat_Random(int NumberPopulation)
	{

		static std::uniform_int_distribution<>distr(0, NumberPopulation - 1);
		size_t index = 0;
		std::vector<size_t>vect(NumberPopulation, 0);

		while (index < NumberPopulation)
		{
			int Number = (int)distr(Generator);
			vect[index++] = Number;
		}
		return vect;
	}


	std::vector<size_t>GeneratePopulation(int NumberPopulation)
	{
		std::vector<size_t> vect(NumberPopulation, 0);
		for (auto i = 0; i < vect.size(); i++)
			vect[i] = i;
		return vect;
	}
	std::vector<size_t>Shuffle(int NumberPopulation, std::vector<size_t>pop)
	{
		std::vector<size_t>population = pop;

		std::shuffle(population.begin(), population.end(), Generator);
		return population;
	}
	std::vector<size_t>Population(int NumberPopulation)
	{
		Generate p;
		std::vector<size_t> sol = p.GeneratePopulation(NumberPopulation);
		sol = p.Shuffle(NumberPopulation, sol);
		return sol;
	}
	
	std::vector<size_t> generatePopulation(int NumberPopulation)
	{
		std::vector<size_t> vect(NumberPopulation, 0);
		for (auto i = 0; i < vect.size(); i++)
			vect[i] = i;
		std::shuffle(vect.begin(), vect.end(), Generator);

		return vect;
	}
	static void PrintSolution(std::vector<size_t>population)
	{
		for (auto const& i : population)
			std::cout << i << " ";

	}
	template <typename T>
	static long double GetRandomFromRange(double  min, double max)
	{
		std::uniform_real_distribution<long double> dist{ min, max - 0.000000000001 };
		return (T)dist(Generator);
	}
};

