#include "Menu.h"

Menu::Menu(Sound & sound, State & state, GLFWwindow* window, Timer& timer)
	: onMainMenu(false)
	, mainMenu(MainMenu::MAIN_START)
	, gameMenu(GameMenu::GAME_EXIT)
	, gameEngineState(state)
	, gameSound(sound)
	, window(window)
	, txt(10, 10, timer)
{
}

void Menu::moveUP()
{
	if (onMainMenu == true)
		mainMenu = static_cast<MainMenu>((mainMenu + 1) % MainMenu::MAIN_LAST);
	else
		gameMenu = static_cast<GameMenu>((gameMenu + 1) % GameMenu::GAME_LAST);
}

void Menu::moveDOWN()
{
	if (onMainMenu == true)
		mainMenu = static_cast<MainMenu>((mainMenu > 0 ?  mainMenu - 1 : mainMenu = static_cast<MainMenu>(MainMenu::MAIN_LAST -1)));
	else
		gameMenu = static_cast<GameMenu>((gameMenu > 0 ? gameMenu - 1 : gameMenu = static_cast<GameMenu>(GameMenu::GAME_LAST - 1)));
}

void Menu::enter()
{
	if (onMainMenu)
	{
		switch (mainMenu)
		{
			case MAIN_START:
			{
				gameEngineState = State::INIT;
				break;
			}
			case MAIN_OPTIONS:
			{

			}
			case MAIN_EXIT:
			{
				gameEngineState = State::EXIT;
				glfwSetWindowShouldClose(window, true);
				break;
			}
		}
	}
	else
	{
		switch (gameMenu)
		{
			case GAME_RESUME:
			{
				gameEngineState = State::GAME;
				break;
			}
			case GAME_OPTIONS:
			{

				break;
			}
			case GAME_TOMAIN:
				break;
			case GAME_EXIT:
			{
				glfwSetWindowShouldClose(window, true);
				break;
			}
			case GAME_LAST:
				break;

		}

	}
}

void Menu::ShowMenu()
{
	txt.setText("RESUME", "RESUME", { 5,5 }, 0);
}
