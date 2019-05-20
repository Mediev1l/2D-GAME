#include "Hero.h"

Hero::Hero(std::string name, double x, double y, double vel, Vec2d OriSize, GLuint nFrames)
	: 
	 Character(name,x,y,OriSize,nFrames)
{
	m_speed = vel;
}
