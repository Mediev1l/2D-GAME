#ifndef TIMER_H
#define TIMER_H
#define _CRT_SECURE_NO_WARNINGS
#include <sstream>
#include <chrono>
#include <ctime>
#include  <map>
class Timer
{
public:
	Timer();
	~Timer();
	double getDelta();
	double getSingleFrameTime();
	double getFPS();
	bool delay(std::string name, size_t secs);
	void Mark();
	std::string date();
	void refresh();
private:
	double delta;
	double maxFPS;
	double SingleFrame;
	std::chrono::system_clock::time_point current;
	std::chrono::system_clock::time_point last;
	std::map<std::string, float> timeCounter;
};
#endif

