/*
Item

Obiekt odpowiedzialny za wszystkie przedmioty w grze

*/

#ifndef _Item_H
#define _Item_H

#include  <fstream>

#include "Basics/Object.h"
#include "Stats/Stats.h"
#include "Basics/Coords.h"
#include "Maps/Tile.h"

class Item : public Object, public Stats
{
protected:
	GLuint id;
	std::string description;
	Texture _texture;
	bool onMap;

public:
	Item(const std::string& TexturePath,const std::string& ItemPath, GLuint itemID);

	double getX() { return posX; };
	double getY() { return posY; };
	bool getOnMap() { return onMap; };
	GLuint getID() { return id; };
	std::string getDescription() { return description; }
	double getVelocity() { return Velocity; };




	void setY(float y) { posY = y; };
	void setX(float x) { posX = x; };
	void setID(GLuint id) { this->id = id; };
	void setDescription(std::string& desc) { description = desc; };
	void setOnMap(bool ex) { onMap = ex; };

	unsigned int getTexture() { return _texture.getID(); };



};

#endif
