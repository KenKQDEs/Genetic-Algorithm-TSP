
#pragma once
#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <stack>
#include <string>
#include <cstring>
#include <vector>
#include <limits>
#include "InputOutput.h"
#include "Experiment.h"

using namespace std;


class Christofides
{
private:

	Experiment ex;
	// List of odd nodes
	vector<int>odds;

	//Smaller cost matrix to find minimum matching on odd nodes
	std::vector<std::vector<long double>> cost;

	//Adjacency list
	vector<int>* adjList;

	void findOdds();

public:
	// Number of cities
	int n;

	//path
	std::vector<std::vector<long double>> path_vals;

	//Shortest path length
	long double pathLength;

	//euler circuit
	vector<int> circuit;

	//vector<City> cities;

	// n x n, pairwise distances between 
	std::vector<std::vector<long double>> graph;

	vector<int>* adjlist;

	// Constructor
	Christofides(Experiment ex);

	// Destructor
	~Christofides();

	int get_distance(struct City c1, struct City c2);

	//Find perfect matching
	void perfectMatching();

	//Find Euler tour
	void euler_tour(int start, vector<int>& path);

	//Find Hamiltonian path
	void make_hamiltonian(vector<int>& path, long double& pathCost);

	// Prim's algorithm
	void findMST();
	

	int getMinIndex(long double key[], bool mst[]);


	int get_size() { return n; };


	long double findBestPath(int start);

	std::vector<int> RunCA();

};
