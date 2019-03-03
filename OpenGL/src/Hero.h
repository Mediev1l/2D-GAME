#ifndef HERO_H
#define HERO_H
#include "Character.h"
#include "Item.h"
class Hero : public Character
{
protected:

public:
	Hero()=delete;
	Hero(double x, double y, double vel, std::string texturepath);
	~Hero() {};
};
#endif