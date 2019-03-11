#include "Animation.h"
Animation::Animation(GLuint frames, double timePerFrame)
	:
	 _dt(timePerFrame)
	,_nFrames(frames)
	,_currentFrame(0)
	,_currentDirection(LEFT)
	,_elapsedTime(0)
{}

Animation::~Animation()
{
}

Vec2i Animation::getAnimationIndex()
{
	//Oblicz index sprite'a
	GLuint x=0;
	for (GLuint i = 0; i < _nFrames; ++i)
	{
		if (_elapsedTime >= _dt * i&&_elapsedTime < _dt*(i + 1)) x = i;
	}
	GLuint y = _currentDirection;
	return Vec2i(x,y);
}

void Animation::UpdateAnimation(Dir dir, double deltaTime)
{
	//Zaktualizuj czas ktory up³yna³
	_elapsedTime += deltaTime;

	//Je¿eli nowy kierunek to dostosuj
	if (dir != _currentDirection)
	{
		_currentDirection = dir;
		_elapsedTime = 0.001;
	}

	if (_elapsedTime > _dt*_nFrames) _elapsedTime = 0.001;
}
