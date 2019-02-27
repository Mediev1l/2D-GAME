
#ifndef _GameEngine_H
#define _GameEngine_H

//================================================================
//= Our libraries
//================================================================
#define STB_IMAGE_IMPLEMENTATION
#include "Renderer/Renderer.h"
#include "Timer.h"
//#include "Maps/Map.h"


//================================================================
//= Windows Libraries
//================================================================
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class GameEngine
{
protected:

	//================================================================
	//= OBJECTS
	//================================================================

	GLFWwindow* window;
	Timer t;
	Renderer renderer;

	//================================================================
	//= GLOBALSETTINGS
	//================================================================
	const unsigned int SCR_WIDTH;
	const unsigned int SCR_HEIGHT;
	float lastX;
	float lastY;
	bool firstMouse;



public:

	GameEngine();

	void Game_Init();
	void Game_Run();

	//================================================================
	//= Window Events Callbacks
	//================================================================
	void framebuffer_size_callback(int width, int height);
	void mouse_callback(double xpos, double ypos);
	void scroll_callback(double xoffset, double yoffset);
	void processInput();



};


#endif // !_GameEngine_H
