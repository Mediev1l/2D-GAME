#include "Hero.h"

Hero::Hero(double x, double y, double vel, double w,  std::string texturepath,std::string PifPafTexturePath)
	: 
	 Character(texturepath, PifPafTexturePath,x,y,w)
{
	m_speed = vel;
	//std::cout << "Id textury hero: " << getTexture() << '\n';
}
