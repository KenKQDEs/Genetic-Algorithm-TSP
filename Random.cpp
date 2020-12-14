#include "Random.h"
#include <vector>
#include <random>


std::random_device RandomHelpers::rd{};
std::mt19937 RandomHelpers::Generator{ rd() };
size_t RandomHelpers::used_times = 0;