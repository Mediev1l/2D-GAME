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
	float getDelta();
	float getSingleFrameTime();
	float getFPS();
	void Mark();
	std::string date();
private:
	float delta;
	float maxFPS;
	float SingleFrame;
	std::chrono::system_clock::time_point current;
	std::chrono::system_clock::time_point last;
};
#endif

