#include "Timer.h"



Timer::Timer() :maxFPS(75), current(), last(), SingleFrame(1/maxFPS)
{
}


Timer::~Timer()
{
}

float Timer::getDelta()
{
	return delta;
}

float Timer::getSingleFrameTime()
{
	return SingleFrame;
}

float Timer::getFPS()
{
	return 1.0f/delta;
}

void Timer::Mark()
{
	if (delta >= 1 / maxFPS) delta = 0;
	last = current;
	current = std::chrono::system_clock::now();
	delta+= std::chrono::duration<float>(current - last).count();
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
