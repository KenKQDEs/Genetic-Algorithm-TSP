#pragma once

#include <chrono>
#include <string>
#include <iostream>
class Timer
{
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_beg;
	std::string Label;
public:
	Timer()
	{
		Label = "Timer";
		m_beg = std::chrono::high_resolution_clock::now();
	}

	Timer(std::string Label)
	{
		this->Label = Label;
		m_beg = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{

		auto diff = std::chrono::high_resolution_clock::now() - m_beg;
		std::cout << Label << ": " << std::chrono::duration_cast<std::chrono::seconds>
									(diff).count()<<"s";
	}
};

