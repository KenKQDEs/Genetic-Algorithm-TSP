#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
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
	
	static std::vector<std::pair<long double, long double>> CitesteCoordonate2D(std::string fileName)
	{
	    std::vector<std::pair<long double, long double>> coords;
	    std::fstream fileStream;
	    std::string linie;
	    fileStream.open(fileName, std::fstream::in);
	    std::getline(fileStream, linie);
	    int NrLinii = 0;
	    sscanf_s(linie.c_str(), "%d", &NrLinii);
	    coords.reserve(NrLinii);
	
	    int i = 1;
	    while (!fileStream.fail() && !fileStream.eof() && i<= NrLinii)
	    {
	        double x, y;
	        std::getline(fileStream, linie);
	        sscanf_s(linie.c_str(), "%Lf %Lf", &x, &y);
	        coords.push_back(std::pair<long double, long double>(x, y));
	        i++;
	    }
	    fileStream.close();
	    return coords;
	}

};

