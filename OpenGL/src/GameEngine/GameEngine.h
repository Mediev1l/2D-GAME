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
#include "Maps/Sonar.h"

#include "Utility/DebugInfo.h"


//================================================================
//= Windows Libraries
//================================================================
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <irrKlang.h>
#include "GameEngine/Menu.h"
class GameEngine
{

protected:
	//================================================================
	//= Console Debug Purpose
	//================================================================
	DebugInfo debuginfo;
	void initInfo();
	void updateInfo();
	void drawInfo();
	//================================================================
	//= OBJECTS
	//================================================================

	GLFWwindow* window;
	Timer t;
	Camera camera;
	Renderer* renderer;
	TextGenerator* textGen;
	Sound soundEngine;
	Sound effectEngine;
	Menu* _Menu;
	Sonar s;
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
	void ProcessShoot(Character& ch);
	void Update();
	void ShowGUI(Vec2d position);
	void HideGUI();
	void HideText();

	void GenNextLevel();

	void ProcessEnemiesMove(double deltaTime);
	void Doors();
	Animation::Direction CalculateDirection(double x, bool pionowo, double margin);
	int CheckColissions(Character& obj, GLuint index, double x, double y);
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
