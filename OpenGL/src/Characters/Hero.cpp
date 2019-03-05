#include "Hero.h"

Hero::Hero(double x, double y, double vel, std::string texturepath,std::string PifPafTexturePath)
	: 
	Character(texturepath, PifPafTexturePath)
{
	posX = x;
	posY = y;
	m_speed = vel;
	//std::cout << "Id textury hero: " << getTexture() << '\n';
}
