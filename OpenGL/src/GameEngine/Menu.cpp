#include "Menu.h"

Menu::Menu(Sound & sound, GameEngine::State & state)
	: onMainMenu(true), mainMenu(MainMenu::mmSTART), gameMenu(GameMenu::gmRESUME), gameEngineState(state), gameSound(&sound)
{
}

void Menu::moveUP()
{
	if (onMainMenu == true)
		mainMenu = static_cast<MainMenu>((mainMenu + 1) % MainMenu::mmLAST);
	else
		gameMenu = static_cast<GameMenu>((gameMenu + 1) % GameMenu::gmLAST);
}

void Menu::moveDOWN()
{
	if (onMainMenu == true)
		mainMenu = static_cast<MainMenu>((mainMenu > 0 ?  mainMenu - 1 : mainMenu = static_cast<MainMenu>(MainMenu::mmLAST -1)));
	else
		gameMenu = static_cast<GameMenu>((gameMenu > 0 ? gameMenu - 1 : gameMenu = static_cast<GameMenu>(GameMenu::gmLAST - 1)));
}

void Menu::enter()
{
	if (onMainMenu)
	{
		switch (mainMenu)
		{
		case mmSTART:
		{
			gameEngineState = GameEngine::State::INIT;
		}
		case mmOPTIONS:
		{

		}
		case mmEXIT:
		{
			gameEngineState = GameEngine::State::EXIT;
		}
		}
	}
}
