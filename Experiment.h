#pragma once
#include <iostream>
#include "BenchmarkFunctions.h"
#include <map>
class Experiment
{
public:
	size_t precision;
	Functions function;
	size_t dimensions;
	size_t solution_size;
	size_t comp_size;
	std::map < Functions, Domain> d =
	{
		{ Functions::Rastrigin,	 Domain(-5.12, 5.12)},
		{ Functions::DeJong1,    Domain(-5.12, 5.12)},
		{ Functions::Schewefel,  Domain(-500, 500) },
		{ Functions::Michalewicz, 	Domain(0, PI) }
	};
	Experiment() = delete;
	Experiment(size_t dimensions, size_t precision, Functions function) : dimensions(dimensions), function(function), precision(precision)
	{
		CalculateBytesNumber(dimensions, precision, d[function]);
	}

	void CalculateBytesNumber(size_t Dims, size_t precision, std::pair<double, double> Interval)
	{
		solution_size = Dims * ceil(log2(pow(10, precision) * (Interval.second - Interval.first)));
		comp_size = solution_size / Dims;
	}
	~Experiment()
	{
		switch (function)
		{
		case Functions::Rastrigin:
			std::cout << "Run experiment on Rastrigin with precision " << precision << " and " << dimensions << " dimensions.";
			break;
		case Functions::DeJong1:
			std::cout << "Run experiment on DeJong1 with precision " << precision << " and " << dimensions << " dimensions.";
			break;
		case Functions::Schewefel:
			std::cout << "Run experiment on Schewefel with precision " << precision << " and " << dimensions << " dimensions.";
			break;
		case Functions::Michalewicz:
			std::cout << "Run experiment on Michalewicz with precision " << precision << " and " << dimensions << " dimensions.";
			break;
		}
	}
};
