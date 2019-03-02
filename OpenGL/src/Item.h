/*
Item

Obiekt odpowiedzialny za wszystkie przedmioty w grze

*/

#ifndef _Item_H
#define _Item_H

#include  <fstream>

#include "Object.h"
#include "Stats.h"
#include "Coords.h"
#include "Maps\Tile.h"

class Item : public Object, Stats
{
protected:
	size_t id;
	std::string description;
	Tile texture;

public:
	Item(const std::string& TexturePath,const std::string& ItemPath, size_t itemID);

	float getX() { return posX; };
	float getY() { return posY; };
	size_t getID() { return id; };
	std::string getDescription() { return description; }
	float getVelocity() { return Velocity; };

	void setY(float y) { posY = y; };
	void setX(float x) { posX = x; };
	void setID(size_t id) { this->id = id; };
	void setDescription(std::string& desc) { description = desc; };

	unsigned int getTexture() { return texture.getID(); };



};

#endif
