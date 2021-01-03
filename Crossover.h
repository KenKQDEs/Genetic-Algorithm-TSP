#pragma once
#include <iostream>
#include  <vector>
#include "Generate.h"
#include "Random.h"
#include <map>
#include <unordered_map>
class Crossover
{
public:
  
    static  std::vector<size_t>SetOffspring(std::vector<size_t>& father, std::vector<size_t>& mother, size_t split)
    {
        size_t size_pop = 0;
        std::unordered_map<size_t, int>occurences;

       
       //size_t split = 6;

        std::vector<size_t> offstringA(father.begin(), father.begin() + split);
        for (auto& num : offstringA)
        {
            occurences[num]++;
        }
        for (auto i = 0; i < mother.size(); i++)
            if (occurences.find(mother[i]) == occurences.end())
            {
                offstringA.push_back(mother[i]);
                
            }
        return offstringA;
    }
    static std::pair< std::vector<size_t>, std::vector<size_t>> Crossoverul(std::vector<size_t>& father, std::vector<size_t>& mother)
    {
        //std::cout << "Crossover"<<std::endl;
        //Generate::PrintSolution(mother);
        //Generate::PrintSolution(father);
        size_t split = RandomHelpers::GetRandomFromRange<int>(1, father.size() - 1);
        auto offstringB = SetOffspring(mother, father, split);
        auto offstringA = SetOffspring(father, mother, split);
        //std::cout << "After" << std::endl;
        //Generate::PrintSolution(mother);
        //Generate::PrintSolution(father);

        return { offstringA, offstringB };

    }
}; 
