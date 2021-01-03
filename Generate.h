#pragma once
#define POP_SIZE 200
#include <random>
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
class Generate
{
	public:
	static std::random_device rd;
	static std::mt19937 Generator;


	static int Rand(size_t a,size_t b)
	{
		static std::uniform_int_distribution<>distr(a, b);
		int Number = (int)distr(Generator);
		return Number;
	}
	
	
	static std::vector<size_t>Generat_Random(int NumberPopulation)
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

	
	static std::vector<size_t> generateSolution(int NumberPopulation)
	{
		std::vector<size_t> vect(NumberPopulation, 0);
		for (auto i = 0; i < vect.size(); i++)
			vect[i] = i;
		std::shuffle(vect.begin(), vect.end(), Generator);

		return vect;
	}
	static std::vector<std::vector<size_t>>generatePopulation(int NumberPopulation)
	{
		std::vector<std::vector<size_t>>Pop;
		std::vector<size_t> vect(POP_SIZE, 0);
		for (auto i = 0; i < POP_SIZE; i++)
		{
			vect=generateSolution(NumberPopulation);
			Pop.push_back(vect);
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	return Pop;
	}
	static void PrintSolution(std::vector<size_t>& solution)
	{
		for (auto const& i : solution)
			std::cout << i << " ";
		std::cout << std::endl;

	}
	static void PrintMatrix(std::vector<std::vector<long double>>& mat,std::ofstream& f)
	{
		for (auto const& vec : mat)
		{
			f << std::endl;
			for (auto const& el : vec)
			{
				f << el << " ";
			}
		}

	}
	template <typename T>
	static long double GetRandomFromRange(double  min, double max)
	{
		std::uniform_real_distribution<long double> dist{ min, max - 0.000000000001 };
		return (T)dist(Generator);
	}
};

