#include "BenchmarkFunctions.h"

long double Michalewicz(std::vector<long double> x, size_t count, const std::pair<double, double>& bounds)
{
	double Sum = 0;

	for (int i = 0; i < count; i++)
	{
		Sum += sin(x[i]) * pow((long double)sin(((long double)(i + 1) * x[i] * x[i]) / PI), 20);
	}
	return -Sum;
}

long double Schwefel(std::vector<long double> x, size_t count, const std::pair<double, double>& bounds)
{
	long double quadraticSum = 0;
	for (int i = 0; i < count; i++)
	{
		quadraticSum += x[i] * sin(sqrt(abs(x[i])));
	}
	return -quadraticSum;
}

long double DeJong1(std::vector<long double> x, size_t count, const std::pair<double, double>& bounds)
{
	long double quadraticSum = 0;

	for (int i = 0; i < count; i++)
	{
		quadraticSum += x[i] * x[i];
	}
	return quadraticSum;
}

long double Rastrigin(std::vector<long double> x, size_t count, const std::pair<double, double>& bounds)
{
	double quadraticSum = 0;

	for (int i = 0; i < count; i++)
	{
		quadraticSum += x[i] * x[i] - 10 * cos(2 * PI * x[i]);
	}

	quadraticSum += 10 * count;
	return quadraticSum;
}