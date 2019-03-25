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
#include "Items/ItemGenerator.h"
#include "Renderer/TextGenerator.h"
#include "GameEngine/Sound.h"

//================================================================
//= Windows Libraries
//================================================================
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <irrKlang.h>
#include <thread>
class GameEngine
{
public:
	//================================================================
	//= GAME ENUM'S
	//================================================================

	enum State
	{
		INIT,
		GAME,
		MENU,
		EXIT
	};

	enum Difficulty
	{
		START,
		EASY,
		MEDIUM,
		HARD
	};

protected:

	//================================================================
	//= OBJECTS
	//================================================================

	GLFWwindow* window;
	Timer t;
	Camera camera;
	Renderer* renderer;
	TextGenerator textGen;
	Sound soundEngine;
	//================================================================
	//= GLOBALSETTINGS
	//================================================================
	const unsigned int SCR_WIDTH;
	const unsigned int SCR_HEIGHT;
	double lastX;
	double lastY;
	bool firstMouse;
	bool _canPickup;
	bool lvlWin;
	State _gameState;
	Difficulty _gameDifficulty;
	//================================================================
	//= Game Objects
	//================================================================
	std::string WindowName;
	std::vector<Character> _characters;
	Map* _map;
	ItemGenerator _ItemGenerator;
	//std::vector<Item*> _items;
	LvlGenerator _lvlgen;

	//================================================================
	//= Game Processor
	//================================================================


	void ProcessPlayerMove(double deltaTime,std::pair<Animation::Direction, Animation::Direction> dir);
	void ProcessItemPickup();
	void ProcessPlayerShoot();
	void Update();

	void ProcessEnemiesMove(double deltaTime);
	void Doors();
	Animation::Direction CalculateDirection(double x, bool pionowo, double margin);
	bool CheckColissions(Character& obj, GLuint index, double x, double y);
	bool ShapeOverlap_DIAGS(Origin &r1, Origin &r2);

	bool CheckCollisionsBullet(Projectile& bullet, GLuint index, double x, double y);

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
