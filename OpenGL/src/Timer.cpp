#include "Timer.h"



Timer::Timer() :maxFPS(75), current(std::chrono::steady_clock::now()), last()
{
}


Timer::~Timer()
{
}

float Timer::getDelta()
{
	return delta.count();
}

float Timer::getGlobalDelta()
{
	return delta.count();
}

float Timer::getSingleFrameTime()
{
	return 1/maxFPS;
}
void Timer::setGlobalDelta(float x)
{
	delta = std::chrono::duration<float>(x);
}
void Timer::Mark()
{
	last = current;
	current = std::chrono::steady_clock::now();
	delta = current - last;
}
