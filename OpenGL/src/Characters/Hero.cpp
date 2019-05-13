#include "Hero.h"

Hero::Hero(std::string name, double x, double y, double vel, Vec2d OriSize, GLuint nFrames, Timer& t)
	: 
	 Character(name,x,y,OriSize,nFrames,t)
{
	m_speed = vel;
}
