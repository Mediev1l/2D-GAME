/*
Character

Obiekt odpowiadajacy za Postac (Glowny Bohater)

// tu jest b³¹d bo po tym obiekcie powinna dziedziczyc klasa enemy i hero 
// + nazwac to inaczej

*/
#ifndef _Character_H
#define _Character_H

#include "Stats/Stats.h"
#include "Basics/Coords.h"
#include "Maps/Tile.h"
#include "Items/Item.h"
#include <vector>

class Character: public Coords, public Stats
{
public:
	Character(std::string TexturePath) : _texture(TexturePath,true), Stats(), Coords() {};
	double getX() { return posX; };
	double getY() { return posY; };
	double getVelocity() { return m_speed; };

	void setY(double y) { posY = y; };
	void setX(double x) { posX = x; };

	void UpdateX(double ux) { posX += ux; };
	void UpdateY(double uy) { posY += uy; };
	GLuint getTexture() { return _texture.getID(); };

	//Mozna skopiowaæ do Hero kwestia przekminy
	void consumeItem(const Item& item);
	//Koniec do przekminiania

protected:

	//Mozna skopiowaæ do Hero kwestia przekminy
	std::vector<Item> _items;
	//Koniec do przekminiania

	//Coords
	Texture _texture;
};
#endif
