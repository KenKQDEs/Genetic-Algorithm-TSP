#pragma once
#include<vector>
class InputOutput
{
public:
	static std::vector<std::vector<long double>>calculateDistance(std::vector<std::pair<long double, long double>>vect)
	{
		std::vector < std::vector<long double>>distante(vect.size(), std::vector<long double>(vect.size()));
		for (auto ii = 0; ii < vect.size(); ii++)
			for (auto jj = 0; jj < vect.size(); jj++)
			{
				distante[ii][jj] = sqrt((vect[jj].first - vect[ii].first) * (vect[jj].first - vect[ii].first) + (vect[jj].second - vect[ii].second) * (vect[jj].second - vect[ii].second));
				if (ii = jj)
					distante[ii][jj] = INT_MAX;
			}

		return distante;

	}

};

