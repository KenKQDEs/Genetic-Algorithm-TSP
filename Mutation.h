#pragma once
#include<vector>
#include<iostream>
#include "Generate.h"
class Mutation
{
public:
	void Mutate(std::vector<size_t>offstringA, std::vector<size_t>offstringB,size_t MutationChange)
	{
		Generate g;
		std::vector<size_t>newoffstringA(offstringA.size(),0);
		std::vector<size_t>newoffstringB(offstringB.size(),0);
		newoffstringA = offstringA;
		newoffstringB = newoffstringB;
		if (g.GetRandomFromRange<long double>(0, 1) < MutationChange)//nu stiu cat e rand() ala din functia  0.2 ar trebui sa fie gen random.NextDouble()
		{
			newoffstringA = mutate(offstringA);
		}
		if (g.GetRandomFromRange<long double>(0, 1) < MutationChange)
		{
			newoffstringB = mutate(offstringB);
		}
	}
	std::vector<size_t> mutate(std::vector<size_t>offString)
	{
		Generate g;
		std::vector<size_t> newoff;
		size_t poz1 = g.Rand(0, offString.size() - 1);
		size_t poz2 = g.Rand(0, offString.size() - 1);
		if (g.GetRandomFromRange<long double>(0,1) > 0.5)//nu stiu cat e rand() ala din functia  0.2 ar trebui sa fie gen random.NextDouble() 
		{
			// Do swap  mutate
			newoff = SwapMutate(offString,poz1,poz2);
		}
		else
		{
			// do rotate mutate
			newoff = RotateMutate(offString, poz1, poz2);
		}
		return newoff;
	}
	std::vector<size_t> SwapMutate(std::vector<size_t>offString,size_t poz1,size_t poz2)
	{
		
	
		std::vector<size_t>newoff = offString;
		auto aux = newoff[poz1];
		newoff[poz1]= newoff[poz2];
		newoff[poz2] = aux;
		return newoff;
	}
	std::vector<size_t>RotateMutate(std::vector<size_t>offString, size_t poz1, size_t poz2)
	{
		std::vector<size_t>h = offString;
		size_t aux;
		size_t p, q;
		if (poz1 < poz2)
		{p = poz1; q = poz2;}
		else { p = poz2; q = poz1; }
		
		
			while (p<q)
			{
				aux = h[p];
				h[p] = h[q];
				h[q] = aux;
				p++;
				q--;
			}

			return h;
	}
};

