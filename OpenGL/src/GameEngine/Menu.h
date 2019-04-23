#ifndef _Menu_H
#define _Menu_H

//#include <GL/glew.h>
//#include "GLFW/glfw3.h"

#include "Utility/Enums.h"
#include "Renderer/Texture.h"
#include "Renderer/TextGenerator.h"
#include "Renderer/Renderer.h"
#include "GameEngine/Sound.h"
#include "Utility/Timer.h"


class Menu 
{
private:
	//=====================
	//Actual State
	//=====================
	ActualPosition position;
	MainMenu mainMenu;
	GameMenu gameMenu;
	GameOptions options;
	GameSoundOptions soundoptions;
	bool _isclosing;

	//=====================
	//Objects
	//=====================
	Texture* texture;
	State& gameEngineState;
	Sound& gameSound;
	Renderer& _gamerenderer;
	GLFWwindow* window; //moze na pozniej
	TextGenerator& _textgen;

	//=====================
	//SETTINGS
	//=====================
	double menux;
	double menuy;
	double xratio;
	double yratio;
	glm::vec4 color;

public:
	Menu() = delete;
	Menu(const Menu& cpy) = delete;
	Menu(Sound& sound, State& state, GLFWwindow* window, TextGenerator& text, Renderer& renderer);

	void moveUP();
	void moveDOWN();
	void MoveLeft();
	void MoveRight();
	void enter();
	void ShowMenu(double x, double y);
	void Close();
	void Open();

	bool isClosed();
	void setClosed(bool close);
private:
	
	void ShowGameMenu();
	void ShowMainMenu();
	void ShowOptions();
	void ShowSound();

	void HideMenu();
	void HideOptions();
	void HideSound();

	void ResetColors();
	void SetColor();
	void setPosition();
	void setGameMenu();
	void setMainMenu();
	void setOptions();
	void setSoundOptions();
};
#endif
