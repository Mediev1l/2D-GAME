/*
Item

Obiekt odpowiedzialny za wszystkie przedmioty w grze

*/

#ifndef _Item_H
#define _Item_H

#include  <fstream>

#include "Basics/Dynamic.h"
#include "Stats/Stats.h"
#include "Basics/Coords.h"
#include "Maps/Tile.h"

class Item : public Dynamic, public Stats
{
public:
	static Texture* _texture;
protected:
	std::string description;
	bool onMap;
	GLuint ID;

public:
	Item();

	void Create(std::string itemdatapath, Texture* text);

	GLuint getID() { return ID; };
	double getX() { return _position.getX(); };
	double getY() { return _position.getY(); };
	bool getOnMap() { return onMap; };
	std::string getDescription() { return description; }

	void setY(float y) { _position.setY(y); };
	void setX(float x) { _position.setX(x); };
	void setDescription(std::string& desc) { description = desc; };
	void setOnMap(bool ex) { onMap = ex; };
	unsigned int getTexture() { return _texture->getID(); };



};


class SpeedBoots: public Item
{
public:
	SpeedBoots();
};

class BMW : public Item
{
public:
	BMW();
};
#endif
