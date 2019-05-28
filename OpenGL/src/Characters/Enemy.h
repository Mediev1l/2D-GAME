/*
Enemy

*/

#ifndef _Enemy_H
#define _Enemy_H
#include "Character.h"

class Enemy: public Character
{
public:
	Enemy(std::string name, double x, double y, double vel, Vec2d OriSize, GLuint nFrames);
	void Behaviour(const Character& player, double deltaTime);
private:
};

#endif