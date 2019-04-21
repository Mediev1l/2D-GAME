#ifndef _Enums_H
#define _Enums_H

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

enum MainMenu
{
	MAIN_START = 0,
	MAIN_OPTIONS = 1,
	MAIN_EXIT = 2,
	MAIN_LAST = 3
};


enum GameMenu
{
	GAME_RESUME = 0,
	GAME_OPTIONS = 1,
	GAME_TOMAIN = 2,
	GAME_EXIT = 3,
	GAME_LAST = 4
};

enum Options
{
	SOUND

};

#endif // !_Enums_H
