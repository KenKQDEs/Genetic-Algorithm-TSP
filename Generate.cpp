#include "Generate.h"
std::random_device Generate::rd{};
std::mt19937 Generate::Generator{ rd() };