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

class Character: public Stats
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

	Character(std::string TexturePath, std::string PifPafTexturePath, double x, double y, double w) 
		: 
		_texture(TexturePath,true)
		,_PifPafTexture(PifPafTexturePath,true)
		, Stats()
		,_tile(true, Tile::Content::Player, Vec2d(x, y), 0, w)
		{};
	double getVelocity() { return m_speed; };
	Dir getSide() { return side; };
	GLuint getPifPafSize() { return (GLuint)_piFpaF.size(); };

	void setSide(Character::Dir sid) { side = sid; };

	std::vector<Projectile>& getpiFpaF() { return _piFpaF; };
	Projectile& getOnepiFpaF(GLuint index) { return _piFpaF[index]; };
	GLuint getPifPafTexture() { return _PifPafTexture.getID(); };

	//void UpdateX(double ux) { posX += ux; };
	//void UpdateY(double uy) { posY += uy; };

	GLuint getTexture() { return _texture.getID(); };

	//Mozna skopiowaæ do Hero kwestia przekminy
	void consumeItem(const Item& item);



	Vec2d getPos() { return _tile.getPos(); };
	void setY(double y) { _tile.getPos().setY(y); };
	void setX(double x) { _tile.getPos().setX(x); };
	Tile& getTile() { return _tile; };

	//virtual void Bechaviour(const Character& player, double deltaTime) = 0;

protected:
	Tile _tile;
	//Mozna skopiowaæ do Hero kwestia przekminy
	std::vector<Item> _items;
	//Koniec do przekminiania

	//Coords
	Texture _texture;
	Texture _PifPafTexture;


	//Weapons
	std::vector<Projectile> _piFpaF;
	//W ktora strone jest zwrocony
	Dir side;
};
#endif
