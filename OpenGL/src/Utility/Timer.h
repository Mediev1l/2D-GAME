#ifndef TIMER_H
#define TIMER_H
#define _CRT_SECURE_NO_WARNINGS
#include <sstream>
#include <chrono>
#include <ctime>
class Timer
{
public:
	Timer();
	~Timer();
	double getDelta();
	double getSingleFrameTime();
	double getFPS();
	void Mark();
	std::string date();
private:
	double delta;
	double maxFPS;
	double SingleFrame;
	std::chrono::system_clock::time_point current;
	std::chrono::system_clock::time_point last;
};
#endif

