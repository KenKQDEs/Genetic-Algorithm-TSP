#pragma once
#include<vector>
#include<iostream>
#include "Generate.h"
class Mutation
{
public:
	static void Mutate(std::vector<size_t>&offstringA, std::vector<size_t>& offstringB,size_t MutationChange)
	{
		Generate g;
		//g.PrintSolution(offstringA);
		//g.PrintSolution(offstringB);
		if (g.GetRandomFromRange<long double>(0, 1) < MutationChange)
		{
			offstringA = mutate(offstringA);
		}
		if (g.GetRandomFromRange<long double>(0, 1) < MutationChange)
		{
			offstringB = mutate(offstringB);
		}
		//g.PrintSolution(offstringA);
		//g.PrintSolution(offstringB);
	}
	static std::vector<size_t> mutate(std::vector<size_t>& offSpring)
	{
		Generate g;
		std::vector<size_t> newoff;
		size_t poz1 = g.Rand(1, offSpring.size() - 1);
		size_t poz2 = g.Rand(1, offSpring.size() - 1);
	
		if (g.GetRandomFromRange<long double>(0,1) > 0.5)//nu stiu cat e rand() ala din functia  0.2 ar trebui sa fie gen random.NextDouble() 
		{
			// Do swap  mutate
			//std::cout << "Swap mutation: \n";
			newoff = SwapMutate(offSpring,poz1,poz2);
		}
		else
		{
			// do rotate mutate
			//std::cout << "Rotation mutation: \n";
			newoff = RotateMutate(offSpring, poz1, poz2);
		}
		return offSpring = newoff;
	}
	static std::vector<size_t> SwapMutate(std::vector<size_t>offString,size_t poz1,size_t poz2)
	{
		
	
		std::vector<size_t>newoff = offString;
		std::swap(newoff[poz1], newoff[poz2]);
		/*auto aux = newoff[poz1];
		newoff[poz1]= newoff[poz2];
		newoff[poz2] = aux;*/
		return newoff;
	}
	static std::vector<size_t>RotateMutate(std::vector<size_t>offString, size_t poz1, size_t poz2)
	{
		std::vector<size_t>rotate = offString;
		size_t aux;
		if (poz1 > poz2)
		{
			std::swap(poz1, poz2);
		}
		
		std::reverse(rotate.begin()+ poz1, rotate.begin()+ poz2 + 1);
		/*
		while (firstIndex<secondIndex)
			{
				std::swap(rotate[firstIndex], rotate[secondIndex]);
				//aux = h[p];
			//	h[p] = h[q];
			//	h[q] = aux;
				firstIndex++;
				secondIndex--;
			}
			*/
			return rotate;
	}
};

