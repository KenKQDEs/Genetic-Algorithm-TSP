

#include <iostream>
#include "GeneticAlg.h"
#include "Christofides.h"

int main()
{
	Experiment ex("inst/lin318.txt");
	GeneticAlg alg(ex);
	//std::vector<size_t> vec = { 1,33,63,16,3,44,32,9,39,72,58,10,31,55,25,50,18,24,49,23,56,41,43,42,64,22,61,21,47,36,69,71,60,70,20,37,5,15,57,13,54,19,14,59,66,65,38,11,53,7,35,8,46,34,52,27,45,29,48,30,4,75,76,67,26,12,40,17,51,6,68,2,74,28,62,73 };
	//for (auto& num : vec)
	//{
	//	num = num - 1;
	//}
	//auto v = alg.CalculateDistance({ 0, 13, 12, 11, 6, 5, 14, 4, 10, 8, 9, 15, 2, 1, 3, 7 }); //1 14 13 12 7 6 15 5 11 9 10 16 3 2 4 8
	//auto v = alg.CalculateDistance(vec); //1 14 13 12 7 6 15 5 11 9 10 16 3 2 4 8
	/*auto res = alg.RunBasicGA();
	auto resres = alg.CalculateDistance(res);*/
	Christofides alg2(ex);

	auto res = alg2.RunCA();
	std::vector<size_t> rezT;
	for (auto& val : res)
	{
		rezT.push_back((size_t)val);
	}
	auto resres = alg.CalculateDistance(rezT);
	std::cout << resres;
}

