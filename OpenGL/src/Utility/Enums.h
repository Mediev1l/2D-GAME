#ifndef _Enums_H
#define _Enums_H

enum State
{
	INIT,
	START,
	GAME,
	MAIN_MENU,
	MENU,
	PAUSE,
	CLOSING_GAME,
	CLOSING_MENU,
	EXIT,
	GAMEOVER
};

enum Difficulty
{
	BEGIN,
	EASY,
	MEDIUM,
	HARD
};

enum class ActualPosition
{
	POSITION_MENU,
	POSITION_MAIN_MENU,
	POSITION_OPTIONS,
	POSITION_SOUND,
	POSITION_GAME,
	POSITION_LAST 
};

enum class Scenario
{
	Normal_Level,
	BossFight
};




#endif // !_Enums_H
