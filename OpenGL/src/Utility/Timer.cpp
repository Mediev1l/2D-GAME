#include "Timer.h"
#include <iostream>



Timer::Timer() :maxFPS(75), current(), last(), SingleFrame(1/maxFPS)
{
}


Timer::~Timer()
{
}

double Timer::getDelta()
{
	return delta;
}

double Timer::getSingleFrameTime()
{
	return SingleFrame;
}

double Timer::getFPS()
{
	return 1.0f/delta;
}

bool Timer::delay(std::string name, size_t secs, bool gametime)
{
	if (timeCounter.find(name) == timeCounter.end())
	{
		timeCounter.emplace(name, std::make_pair(secs, gametime));
		return true;
	}
	else
	{
		if (timeCounter[name].first <= 0)
		{
			timeCounter[name].first = (float)secs ;
			return true;
		}
	}

	return false;
}

void Timer::Mark()
{
	if (delta >= 1 / maxFPS) delta = 0;
	last = current;
	current = std::chrono::system_clock::now();
	delta+= std::chrono::duration<double>(current - last).count();

}

void Timer::Reset()
{
	std::map<std::string, std::pair<float, bool>>::iterator it;

	for (it = timeCounter.begin(); it != timeCounter.end(); it++)
	{
		if (it->second.second == true)
			if (it->second.first > 0) it->second.first = 0;

	}
}

bool Timer::CheckState(std::string name)
{
	if (timeCounter[name].first <= 0)
	{
		return false;
	}
	else
		return true;
}

std::string Timer::date()
{
	std::stringstream tmp;
	std::time_t t = std::time(0);   // get time now
	std::tm* now = std::localtime(&t);
	tmp << (now->tm_year + 1900) << '-'
		<< (now->tm_mon + 1) << '-'
		<< now->tm_mday << " "
		<< now->tm_hour << ":"
		<< now->tm_min << ":"
		<< now->tm_sec << "\n";
	return tmp.str();
}

void Timer::refresh(bool ingame)
{
	std::map<std::string, std::pair<float,bool>>::iterator it;
	
	for (it = timeCounter.begin(); it != timeCounter.end(); it++)
	{
		if (it->second.second == ingame)
		{

			if (it->second.first > 0) it->second.first -= (float)delta ;
		}

	}
	
}
