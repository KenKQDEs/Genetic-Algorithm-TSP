#pragma once
#include <iostream>

class Experiment
{
public:
	size_t TownNumber;
	unsigned long TotalDistance = 0;

	Experiment() = delete;
	Experiment(size_t TownNumber) : TownNumber(TownNumber)
	{
		
	}

	~Experiment()
	{
		std::cout << "Run an experiment on " << TownNumber << "number of towns" << std::endl;
	}
};
