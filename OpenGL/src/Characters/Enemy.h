/*
Enemy

*/

#ifndef _Enemy_H
#define _enemy_H
#include "Character.h"

class Enemy: public Character
{
public:
	Enemy(std::string name, double x, double y, double vel, Vec2d OriSize, GLuint nFrames,Timer& t);
	void Bechaviour(const Character& player, double deltaTime);
private:
};

#endif