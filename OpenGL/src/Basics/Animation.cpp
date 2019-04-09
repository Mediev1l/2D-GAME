#include "Animation.h"
Animation::Animation(GLuint frames, double timePerFrame)
	:
	 _dt(timePerFrame)
	,_nFrames(frames)
	,_currentFrame(0)
	,_currentDirection(Direction::NONE,Direction::NONE)
	,_elapsedTime(0)
{}

Animation::~Animation()
{}

Vec2i Animation::getAnimationIndex()
{
	//Oblicz index sprite'a
	GLuint x=0;
	for (GLuint i = 0; i < _nFrames; ++i)
	{
		if (_elapsedTime >= _dt * i&&_elapsedTime < _dt*(i + 1)) x = i;
	}

	//Preferuj ruch w lewo prawo, je¿eli wystêpuj¹ oba na raz.
	GLuint y = _currentDirection.first != Direction::NONE
				 &&
				_currentDirection.second == Direction::NONE
				? (GLuint)_currentDirection.first : (GLuint)_currentDirection.second;
	return Vec2i(x,y);
}


void Animation::UpdateAnimation(std::pair<Direction,Direction> dir, double deltaTime)
{
	if (dir.first != Direction::NONE || dir.second != Direction::NONE)
	{
		//Zaktualizuj czas ktory up³yna³
		_elapsedTime += deltaTime;

		//Je¿eli nowy kierunek to dostosuj
		if (dir.first != _currentDirection.first || dir.second != _currentDirection.second)
		{
			_currentDirection.first = dir.first;
			_currentDirection.second = dir.second;
			_elapsedTime = 0.001;
		}

		if (_elapsedTime > _dt*_nFrames) _elapsedTime = 0.001;
	}
	else
	{
		_elapsedTime = 0.0;
	}
}
