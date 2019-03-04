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
#include "Weapons/Projectile.h"
#include <vector>

class Character: public Coords, public Stats
{
public:

	enum Dir
	{
		NONE = -1,
		UP = 0,
		DOWN = 1,
		LEFT = 2,
		RIGHT = 3

	};

	Character(std::string TexturePath) : _texture(TexturePath,true), Stats(), Coords() {};
	double getX() { return posX; };
	double getY() { return posY; };
	double getVelocity() { return m_speed; };
	Dir getSide() { return side; };
	GLuint getPifPafSize() { return _piFpaF.size(); };

	void setY(double y) { posY = y; };
	void setX(double x) { posX = x; };
	void setSide(Character::Dir sid) { side = sid; };

	std::vector<Projectile>& getpiFpaF() { return _piFpaF; };
	Projectile& getOnepiFpaF(GLuint index) { return _piFpaF[index]; };
	

	void UpdateX(double ux) { posX += ux; };
	void UpdateY(double uy) { posY += uy; };
	GLuint getTexture() { return _texture.getID(); };

	//Mozna skopiowaæ do Hero kwestia przekminy
	void consumeItem(const Item& item);



	//Koniec do przekminiania

	//virtual void Bechaviour(const Character& player, double deltaTime) = 0;

protected:

	//Mozna skopiowaæ do Hero kwestia przekminy
	std::vector<Item> _items;
	//Koniec do przekminiania

	//Coords
	Texture _texture;

	//Weapons
	std::vector<Projectile> _piFpaF;

	//W ktora strone jest zwrocony
	Dir side;
};
#endif
