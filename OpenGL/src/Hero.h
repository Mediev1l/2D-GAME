#ifndef HERO_H
#define HERO_H
#include "Character.h"
#include "Item.h"
class Hero : public Character
{
protected:

public:
	Hero()=delete;
	Hero(float x, float y, float vel, std::string texturepath);
	~Hero() {};
};
#endif