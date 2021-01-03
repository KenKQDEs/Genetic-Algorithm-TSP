#include <vector>
#include <algorithm>
#include <iterator>
#include <vector>
#pragma once
std::vector<long double> ConvertBack(std::vector<char>& bytes, const std::pair<double, double>& Interval, size_t bytesNo);
long double ConvertBits(std::vector<char>& op, const std::pair<double, double>& Interval);
void PrintCharBytes(std::vector<char>& bytes);
bool SameByteVector(std::vector<char>& a, std::vector<char>& b);



template<typename Vector>
auto split_vector(const Vector& v, unsigned number_lines) 
{
    using Iterator = typename Vector::const_iterator;
    std::vector<Vector> rtn;
    Iterator it = v.cbegin();
    const Iterator end = v.cend();

    while (it != end) {
        Vector v;
        std::back_insert_iterator<Vector> inserter(v);
        const auto num_to_copy = std::min(static_cast<unsigned>(
            std::distance(it, end)), number_lines);
        std::copy(it, it + num_to_copy, inserter);
        rtn.push_back(std::move(v));
        std::advance(it, num_to_copy);
    }

    return rtn;
}