

#ifndef _Timer_H
#define _Timer_H

#include "GLFW\glfw3.h"
#include <chrono>
class Timer
{
public:
	Timer();
	~Timer();
	float getDelta();
	float getGlobalDelta();
	float getSingleFrameTime();
	void setGlobalDelta(float x);
	void Mark();
private:
	std::chrono::steady_clock::time_point current;
	std::chrono::steady_clock::time_point last;
	std::chrono::duration<float> delta;
	float maxFPS;
};



#endif 


