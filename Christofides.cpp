
#include "Christofides.h"


//Constructor
Christofides::Christofides(Experiment ex)  : ex(ex)
{

	n = ex.TownNumber;

	graph.resize(n);
	//cost.reserve(n);
	path_vals.resize(n);
	for (int i = 0; i < n; i++)
	{
		graph[i].resize(n);
		//cost[i].reserve(n);
		path_vals[i].resize(n);
	}
	graph = ex.distance;



	adjlist = new vector<int>[n];
}

//Destructor
Christofides::~Christofides() {
	/*for (int i = 0; i < n; i++) {
		delete[] graph[i];
		delete[] cost[i];
		delete[] path_vals[i];
	}
	delete[] path_vals;
	delete[] graph;
	delete[] cost;*/
	delete[] adjlist;
}



void Christofides::findMST() 
{
	//prim
	long double* key = new long double[n];
	bool* included = new bool[n];
	int* parent = new int[n];

	for (int i = 0; i < n; i++) 
	{
		key[i] = std::numeric_limits<int>::max();
		included[i] = false;
	}

	key[0] = 0;
	parent[0] = -1;

	for (int i = 0; i < n - 1; i++) 
	{
		int k = getMinIndex(key, included);
		included[k] = true;

		for (int j = 0; j < n; j++) 
		{

			if (graph[k][j] !=INT_MAX && included[j] == false && graph[k][j] < key[j]) 
			{

				parent[j] = k;

				key[j] = graph[k][j];

			}
		}

	}

	for (int i = 0; i < n; i++) {

		int j = parent[i];

		if (j != -1) {

			adjlist[i].push_back(j);
			adjlist[j].push_back(i);

		}

	}

}




int Christofides::getMinIndex(long double key[], bool mst[])
{

	int min = std::numeric_limits<int>::max();
	int min_index = 0;

	for (int i = 0; i < n; i++) {

		
		if (mst[i] == false && key[i] < min)
		{

	
			min = key[i];
			min_index = i;

		}

	}

	return min_index;

}


void Christofides::findOdds() {

	for (int i = 0; i < n; i++) {

		if ((adjlist[i].size() % 2) != 0) {

			odds.push_back(i);

		}

	}

}


void Christofides::perfectMatching() 
{

	int closest, length;
	std::vector<int>::iterator tmp, first;

	findOdds();

	while (!odds.empty()) 
	{
		first = odds.begin();
		vector<int>::iterator it = odds.begin() + 1;
		vector<int>::iterator end = odds.end();
		length = std::numeric_limits<int>::max();
		for (; it != end; ++it) 
		{

			if (graph[*first][*it] < length) {
				length = graph[*first][*it];
				closest = *it;
				tmp = it;
			}
		}
		adjlist[*first].push_back(closest);
		adjlist[closest].push_back(*first);
		odds.erase(tmp);
		odds.erase(first);
	}
}



void Christofides::euler_tour(int start, vector<int>& path) {
	
	vector<int>* tempList = new vector<int>[n];
	for (int i = 0; i < n; i++) {
		tempList[i].resize(adjlist[i].size());
		tempList[i] = adjlist[i];
	}

	stack<int> stack;
	int pos = start;
	path.push_back(start);
	while (!stack.empty() || tempList[pos].size() > 0) {
		
		if (tempList[pos].empty()) 
		{

			path.push_back(pos);
			pos = stack.top();
			stack.pop();
		}
		else
		{
			stack.push(pos);
			int neighbor = tempList[pos].back();
			tempList[pos].pop_back();
			for (int i = 0; i < tempList[neighbor].size(); i++) {
				if (tempList[neighbor][i] == pos) {
					tempList[neighbor].erase(tempList[neighbor].begin() + i);
				}
			}
			pos = neighbor;
		}
	}
	path.push_back(pos);
}


void Christofides::make_hamiltonian(vector<int>& path, long double& pathCost) {

	bool* visited = new bool[n];
	for (int i = 0; i < n; i++) {
		visited[i] = 0;
	}

	pathCost = 0;

	int root = path.front();
	vector<int>::iterator cur = path.begin();
	vector<int>::iterator iter = path.begin() + 1;
	visited[root] = 1;

	bool addMore = true;
	while (iter != path.end()) 
	{
		if (!visited[*iter]) 
		{
			pathCost += graph[*cur][*iter];
			cur = iter;
			visited[*cur] = 1;
			iter = cur + 1;
		}
		else
		{
			iter = path.erase(iter);
		}
	}
	if (iter != path.end()) {
		pathCost += graph[*cur][*iter];
	}
}

long double Christofides::findBestPath(int start) {
	vector<int> path;
	euler_tour(start, path);
	long double length;

	make_hamiltonian(path, length);
	return length;
}

std::vector<int> Christofides::RunCA()
{
	int tsp_size = ex.TownNumber;
	findMST();

	int best = INT_MAX;
	int bestIndex;
	for (long t = 0; t < tsp_size; t++) {
		int result = findBestPath(t);

		path_vals[t][0] = t; 
		path_vals[t][1] = result;

		if (path_vals[t][1] < best) {
			bestIndex = path_vals[t][0];
			best = path_vals[t][1];
		}
	}

	euler_tour(bestIndex, circuit);
	make_hamiltonian(circuit, pathLength);
	//std::cout << "Final length:" << pathLength;
	return circuit;
}




