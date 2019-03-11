#ifndef ANIMATION_H
#define ANIMATION_H
#include "Renderer/Texture.h"
#include "GL/glew.h"
#include "Utility/Vec2.h"
class Character;

class Animation
{
public:
	enum Dir
	{
		NONE = -1,
		DOWN = 0,
		UP = 1,
		LEFT = 2,
		RIGHT = 3
	};
//================================================================
//= Konstruktory
//================================================================
	Animation(GLuint frames, double timePerFrame);
	~Animation();
//================================================================
//= Interakcja
//================================================================
	Vec2i getAnimationIndex();
	void UpdateAnimation(Dir x, double deltaTime);
private:
	double _dt;
	double _elapsedTime;
	GLuint _nFrames;
	GLuint _currentFrame;
	Dir _currentDirection;
};

#endif