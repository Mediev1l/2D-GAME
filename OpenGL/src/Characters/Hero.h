#ifndef HERO_H
#define HERO_H
#include "Characters/Character.h"
#include "Items/Item.h"
class Hero : public Character
{
protected:

public:
	Hero()=delete;
	Hero(std::string name, double x, double y, double vel, Vec2d OriSize, GLuint nFrames);
	void Bechaviour(const Character& player, double deltaTime) {};
	~Hero() {};
protected:
};
#endif