#ifndef _Menu_H
#define _Menu_H

#include <GL/glew.h>
#include "GLFW/glfw3.h"

#include "Utility/Enums.h"
#include "Renderer/Texture.h"
#include "GameEngine/Sound.h"
#include "Renderer/TextGenerator.h"
#include "Utility/Timer.h"


class Menu 
{
private:
	//=====================
	//Actual State
	//=====================
	MainMenu mainMenu;
	GameMenu gameMenu;
	bool onMainMenu;

	//=====================
	//Objects
	//=====================
	Texture* texture;
	State& gameEngineState;
	Sound& gameSound;
	GLFWwindow* window;
	TextGenerator txt;
	


public:
	Menu() = delete;
	Menu(Sound& sound, State& state, GLFWwindow* window, Timer& timer);

	void setGameMenu() { onMainMenu = false; gameMenu = GameMenu::GAME_RESUME; };
	void setMainMenu() { onMainMenu = true; mainMenu = MainMenu::MAIN_START; };
	void moveUP();
	void moveDOWN();
	void enter();
	void ShowMenu();

};
#endif
