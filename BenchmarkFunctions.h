#pragma once
#define PI 3.1415926
#include <functional>
#include <vector>

enum class Functions
{
	Rastrigin,
	DeJong1,
	Schewefel,
	Michalewicz
};
using UsualFunction = std::function<long double(std::vector<long double>, size_t, std::pair<double, double>&)>;
using Domain = std::pair<double, double>;

long double Rastrigin(std::vector<long double> x, size_t count, const std::pair<double, double>& bounds);



long double DeJong1(std::vector<long double> x, size_t count, const std::pair<double, double>& bounds);



long double Schwefel(std::vector<long double> x, size_t count, const std::pair<double, double>& bounds);




long double Michalewicz(std::vector<long double> x, size_t count, const std::pair<double, double>& bounds);
