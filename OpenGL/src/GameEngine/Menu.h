#ifndef _Menu_H
#define _Menu_H

#include "GameEngine/GameEngine.h"


class Menu
{
public:
	enum MainMenu
	{
		mmSTART = 0,
		mmOPTIONS = 1,
		mmEXIT = 2,
		mmLAST = 3
	};


	enum GameMenu
	{
	gmRESUME = 0,
	gmOPTIONS = 1,
	gmTOMAIN = 2,
	gmEXIT = 3,
	gmLAST = 4
	};
private:

	Texture* texture;
	MainMenu mainMenu;
	GameMenu gameMenu;
	GameEngine::State& gameEngineState;
	Sound* gameSound;
	bool onMainMenu;


public:
	Menu() = delete;
	Menu(Sound& sound, GameEngine::State& state);

	void setGameMenu() { onMainMenu = false; gameMenu = GameMenu::gmRESUME; };
	void setMainMenu() { onMainMenu = true; mainMenu = MainMenu::mmSTART; };
	void moveUP();
	void moveDOWN();
	void enter();

};
#endif
