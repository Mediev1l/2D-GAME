#include "Hero.h"

Hero::Hero(std::string name, double x, double y, double vel, double w)
	: 
	 Character(name,x,y,w)
{
	m_speed = vel;
}
