#include "Hero.h"

Hero::Hero(float x, float y, float vel, std::string texturepath): Character(texturepath)
{
	posX = x;
	posY = y;
	Velocity = vel;
	//std::cout << "Id textury hero: " << getTexture() << '\n';
}
