#include "Hero.h"

Hero::Hero(std::string name, double x, double y, double vel, double w, GLuint nFrames)
	: 
	 Character(name,x,y,w,nFrames)
{
	m_speed = vel;
}
