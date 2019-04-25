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

enum class ActualPosition
{
	POSITION_MENU,
	POSITION_MAIN_MENU,
	POSITION_OPTIONS,
	POSITION_SOUND,
	POSITION_LAST 
};




#endif // !_Enums_H
