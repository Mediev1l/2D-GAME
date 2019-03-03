#include "Hero.h"

Hero::Hero(double x, double y, double vel, std::string texturepath)
	: 
	Character(texturepath)
{
	posX = x;
	posY = y;
	m_speed = vel;
	//std::cout << "Id textury hero: " << getTexture() << '\n';
}
