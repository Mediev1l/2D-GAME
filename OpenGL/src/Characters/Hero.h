#ifndef HERO_H
#define HERO_H
#include "Characters/Character.h"
#include "Items/Item.h"
class Hero : public Character
{
protected:

public:
	Hero()=delete;
	Hero(double x, double y, double vel, std::string texturepath, std::string PifPafTexturePath);
	void Bechaviour(const Character& player, double deltaTime) {};
	~Hero() {};
};
#endif