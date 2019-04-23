#ifndef _Enums_H
#define _Enums_H

enum State
{
	INIT,
	GAME,
	MENU,
	PAUSE,
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

enum ActualPosition
{
	POSITION_MENU,
	POSITION_MAIN_MENU,
	POSITION_OPTIONS,
	POSITION_SOUND,
	POSITION_LAST 
};

enum GameOptions
{
	GAME_OPTIONS_SOUND = 0,
	GAME_OPTIONS_BACK = 1,
	GAME_OPTIONS_LAST = 2
};

enum GameSoundOptions
{
	GAME_SOUND_MUTE = 0,
	GAME_SOUND_VOLUME = 1,
	GAME_SOUND_BACK = 2,
	GAME_SOUND_LAST = 3
};

enum MainSoundOptions
{
	MAIN_SOUND_MUTE = 0,
	MAIN_SOUND_VOLUME = 1,
	MAIN_SOUND_THEME = 2,
	MAIN_SOUND_BACK = 3,
	MAIN_SOUND_LAST = 4
};

#endif // !_Enums_H
