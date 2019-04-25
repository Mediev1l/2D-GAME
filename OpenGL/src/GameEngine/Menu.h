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
#include <array>


class Menu 
{
private:

	struct Selection
	{
		std::vector<std::string> names;

	};


	//=====================
	//Actual State
	//=====================
	ActualPosition position;
	Selection _menu;
	Selection _options;
	Selection _sounds;
	bool _isclosing;
	int _cursor;

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



	void SetColor();
	void setCursor(int position);
	void PositionReset();

};
#endif
