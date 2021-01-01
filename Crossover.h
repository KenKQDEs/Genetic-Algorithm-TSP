#pragma once
#include <iostream>
#include<vector>
#include "Generate.h"
#include "Rand.h"
#include <map>
#include <unordered_map>
class Crossover
{
public:
  
    static  std::vector<size_t>SetOff(size_t nr_orase, std::vector<size_t>& father, std::vector<size_t>& mother)
    {
        size_t size_pop = 0;
        std::unordered_map<size_t, int>occurences;

       size_t split = RandomHelpers::GetRandomFromRange<int>(1, father.size() - 1);
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
    static std::pair< std::vector<size_t>, std::vector<size_t>> Crossoverul(size_t nr_orase, std::vector<size_t>& father, std::vector<size_t>& mother)
    {

        auto offstringB = SetOff(nr_orase, mother, father);
        auto offstringA = SetOff(nr_orase, father, mother);

        return { offstringA, offstringB };

    }
}; 
