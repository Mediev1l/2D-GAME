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
	bool delay(std::string name, size_t secs, bool gametime);
	void Mark();
	void Reset();
	bool CheckState(std::string name);
	std::string date();
	void refresh(bool ingame);
private:
	double delta;
	double maxFPS;
	double SingleFrame;
	std::chrono::system_clock::time_point current;
	std::chrono::system_clock::time_point last;
	std::map<std::string, std::pair<float, bool>> timeCounter;
};
#endif

