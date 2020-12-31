#pragma once
#include <iostream>
#include<vector>
#include "Generate.h"
class Crossover
{
 public:
	//father = [ ff | ss ]

//mother = [ gg | cc]

//offstring A=ff cc
//offstring B=gg ss
//luam ff din father si verificam in tot mother daca exista valori de genul si apoi valorile ce raman le punem in mother
//
	static std::vector<size_t>SetOffstring(size_t nr_population, std::vector<size_t>parent1, std::vector<size_t>parent2)
	{
		std::vector<size_t> offstringA(nr_population, 0);
		size_t size_pop = 0;
		size_t split = parent1.size() / 2 + 1;
	
		for (int i = 0; i < split; i++)
		{
			offstringA[size_pop++] = parent1[i];
		}
		bool ok;
		size_t i;
		for (i = 0; i < parent2.size(); i++)

		{
			ok = 0;
			for (int j = 0; j < offstringA.size(); j++)
			{
				if (offstringA[j] == parent2[i])
				{
					ok = 1; break;
				}

			}
			if (ok == 0)
				offstringA[size_pop++] = parent2[i];
		}
		return offstringA;
	}

  static void Crossoverul(size_t nr_population, std::vector<size_t>&offstringA, std::vector<size_t>&offstringB)
	{
	  std::vector<size_t> father, mother;

	  size_t size_pop=0;
	 
	  Generate p;
		father = p.Population(nr_population);
		mother = p.Population(nr_population);
		offstringA = SetOffstring(nr_population, father, mother);
		offstringB = SetOffstring(nr_population, mother, father);
	
  }
};

