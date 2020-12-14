#pragma once
#include <random>
#include <iostream>
class RandomHelpers
{
public :
	static std::random_device rd;

	static std::mt19937 Generator;

	static size_t used_times ;

	template<typename T>
	static void PrintResult(std::vector<T> result)
	{
		for (const T& byte : result)
		{
			std::cout << byte << " ";
		}
		std::cout << std::endl;
	}
	//Generates little endian bitarray
	static std::vector<char> GenerateBitArray(int BitCount)
	{
		std::uniform_int_distribution<int> dist{ 0, 1 };
		std::vector<char> Generated(BitCount, 0);
		size_t index = 0;
		while (index < BitCount)
		{
			used_times++;
			long Number = (long)dist(Generator);
			Generated[index++] = Number % 2;
		}
		//std::cout << "Generated number:";
		//PrintResult(Generated);
		return Generated;
	}
	static std::vector<std::vector<char>> GenerateRandomPopulation(int popSize, int bitsCount)
	{
		std::vector<std::vector<char>> population(popSize);
		for (size_t i = 0; i < popSize; i++)
		{
			population[i] = GenerateBitArray(bitsCount);
		}
		return population;
	}
	static std::vector<std::vector<char>> GenerateRandomUniformPopulation(int popSize, int bitsCount)
	{
		std::vector<std::vector<char>> population(popSize);
		std::vector<char> mask(bitsCount, 1);
		for (size_t i = 0; i < popSize; i++)
		{
			population[i] = mask;
			mask[i] = 0;
			for (int j = i + 1; j < mask.size(); j++)
			{
				if (RandomHelpers::GetRandomFromRange<long double>(0, 1) <= 0.01)
				{
					population[i][j] = 0;
				}
			}
		}
		return population;
	}
	template <typename T>
	static long double GetRandomFromRange(double  min, double max)
	{
		std::uniform_real_distribution<long double> dist{ min, max - 0.000000000001 };
		return (T)dist(Generator);
	}
};

