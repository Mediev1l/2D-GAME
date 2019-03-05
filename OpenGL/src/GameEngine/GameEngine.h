
#ifndef _GameEngine_H
#define _GameEngine_H

//================================================================
//= Our libraries
//================================================================
#include "Renderer/Renderer.h"
#include "Utility/Timer.h"
#include "Characters/Hero.h"
#include "Characters/Enemy.h"


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
	bool _canPickup;
	double delay;
	//================================================================
	//= Game Objects
	//================================================================
	std::string WindowName;
	std::vector<Character> _characters;
	Map* _map;
	std::vector<Item> _items;


	//================================================================
	//= Game Processor
	//================================================================
	enum Direction
	{
		UP=0,
		DOWN=1,
		LEFT=2,
		RIGHT=3,
		NONE=4
	};

	void ProcessPlayerMove(double deltaTime,Direction dir);
	void ProcessItemPickup();
	void ProcessPlayerShoot();
	void Update();

	//void ProcessEnemiesMove(double deltaTime);
	void OpenDoors();
	void CloseDoors();

	bool ShapeOverlap_DIAGS(Tile &r1, Tile &r2);

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
