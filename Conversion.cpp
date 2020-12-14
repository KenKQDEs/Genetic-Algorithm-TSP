#include "Conversion.h"
#include <iostream>
std::vector<long double> ConvertBack(std::vector<char>& bytes, const std::pair<double, double>& Interval, size_t bytesNo)
{
		int count = bytes.size() / bytesNo;
		std::vector<long double> x;

		auto componente = split_vector(bytes, bytesNo);

		for (auto& componenta : componente)
		{
			x.push_back(ConvertBits(componenta, Interval));
		}

		return x;
}
long double ConvertBits(std::vector<char>& op, const std::pair<double, double>& Interval)
{
	long double value = 0;
	for (int ii = 0; ii < op.size(); ii++)
	{
		value = value * 2;
		value += (int)op[ii];
	}
	long double xi = 0;
	xi = value / (pow(2, op.size()) - 1);
	xi = xi * (Interval.second - Interval.first) + Interval.first;
	return xi;
}

void PrintCharBytes(std::vector<char>& bytes)
{
	std::cout << std::endl;
	for (int i = 0; i < bytes.size(); i++)
	{
		std::cout << (char)(bytes[i] + 48);
	}
	std::cout << std::endl;
}

bool SameByteVector(std::vector<char>& a, std::vector<char>& b)
{
	for (int i = 0; i < a.size(); i++)
	{
		if (a[i] != b[i]) return false;
	}
	return true;
}