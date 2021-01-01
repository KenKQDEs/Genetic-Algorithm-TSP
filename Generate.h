#pragma once
#define POP_SIZE 100
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

	
	std::vector<size_t> generatePop(int NumberPopulation)
	{
		std::vector<size_t> vect(NumberPopulation, 0);
		for (auto i = 0; i < vect.size(); i++)
			vect[i] = i;
		std::shuffle(vect.begin(), vect.end(), Generator);

		return vect;
	}
	std::vector<std::vector<size_t>>generatePopulation()
	{
		std::vector<std::vector<size_t>>Pop;
		std::vector<size_t> vect(POP_SIZE, 0);
		for (auto i = 0; i < POP_SIZE; i++)
		{
			for (auto ii = 0; ii < vect.size(); ii++)
				vect[ii] = ii;
			std::shuffle(vect.begin(), vect.end(), Generator);
			Pop.push_back(vect);
		}

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

