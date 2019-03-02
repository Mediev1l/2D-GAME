
#ifndef _GameEngine_H
#define _GameEngine_H

//Nie wiem dlaczego wywala b³¹d jak to nie jest w Main.cpp
//#define STB_IMAGE_IMPLEMENTATION
//================================================================
//= Our libraries
//================================================================
#include "Renderer/Renderer.h"
#include "Utility/Timer.h"
#include "Hero.h"


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
	Renderer* renderer;

	//================================================================
	//= GLOBALSETTINGS
	//================================================================
	const unsigned int SCR_WIDTH;
	const unsigned int SCR_HEIGHT;
	double lastX;
	double lastY;
	bool firstMouse;
	std::string WindowName;
	std::vector<Character> _characters;
	Map* _map;
	Item* _item;
	void CheckForPlayerColissionX(float deltaTime, bool left);
	void CheckForPlayerColissionY(float deltaTime, bool top);

public:

	GameEngine();
	~GameEngine() { delete renderer; };

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
