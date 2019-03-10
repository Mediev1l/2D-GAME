
#ifndef _GameEngine_H
#define _GameEngine_H

//================================================================
//= Our libraries
//================================================================
#include "Renderer/Renderer.h"
#include "Utility/Timer.h"
#include "Characters/Hero.h"
#include "Characters/Enemy.h"
#include "Renderer/Camera.h"
#include "Maps/LvlGenerator.h"


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
	Camera camera;
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
	bool lvlWin;
	//================================================================
	//= Game Objects
	//================================================================
	std::string WindowName;
	std::vector<Character> _characters;
	Map* _map;
	std::vector<Item> _items;
	LvlGenerator _lvlgen;

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

	void ProcessEnemiesMove(double deltaTime);
	void Doors();
	GameEngine::Direction CalculateDirection(double x, bool pionowo, double margin);
	bool CheckColissions(const Character& obj, GLuint index, double x, double y);
	bool ShapeOverlap_DIAGS(Tile &r1, Tile &r2);

	bool CheckCollisionsBullet(const Projectile& bullet, GLuint index, double x, double y);

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
