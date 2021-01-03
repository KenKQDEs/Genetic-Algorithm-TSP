#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "InputOutput.h"
#include "Generate.h"
class Experiment
{
public:
	size_t TownNumber;
	unsigned long TotalDistance = 0;
	std::vector<std::vector<long double>> distance;
	
	Experiment() = delete;
	Experiment(std::string fileName)
	{
		std::ofstream writeOutput("Resz.txt");
		for (auto& vec : distance)
		{
			vec.reserve(TownNumber);
		}
		auto rez = InputOutput::CitesteCoordonate2D(fileName);
		TownNumber = rez.size();
		distance = InputOutput::calculateDistance(rez);
		Generate::PrintMatrix(distance, writeOutput);
	}

	~Experiment()
	{
		std::cout << "Run an experiment on " << TownNumber << "number of towns" << std::endl;
	}
};
