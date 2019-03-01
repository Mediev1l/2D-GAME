/*
Character

Obiekt odpowiadajacy za Postac (Glowny Bohater)

// tu jest b³¹d bo po tym obiekcie powinna dziedziczyc klasa enemy i hero 
// + nazwac to inaczej

*/
#ifndef _Character_H
#define _Character_H

#include "Stats.h"
#include "Coords.h"
#include "Maps/Tile.h"

class Character: public Coords, Stats
{
public:
	Character(std::string TexturePath) : texture(TexturePath,true) {};
	float getX() { return posX; };
	float getY() { return posY; };
	float getVelocity() { return Velocity; };
	void UpdateX(float ux) { posX += ux; };
	void UpdateY(float uy) { posY += uy; };
	unsigned int getTexture() { return texture.getID(); };
protected:
	//Coords
	Tile texture;
};
#endif
