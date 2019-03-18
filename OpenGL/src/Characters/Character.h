//================================================================
//= Postaæ, baza dla gracza i NPC
//================================================================
#ifndef _Character_H
#define _Character_H

#include "Stats/Stats.h"
#include "Basics/Dynamic.h"
#include "Maps/Tile.h"
#include "Items/Item.h"
#include "Weapons/Projectile.h"
#include "Basics/Animation.h"
#include <vector>

class AssetManager;
class Character: public Stats, public Dynamic
{
public:

//================================================================
//= Konstruktory
//================================================================
	Character(std::string name, double x, double y, double w, GLuint nFrames);
	
//================================================================
//= Gettery
//================================================================
	double getVelocity() { return m_speed; };
	Animation::Direction getSide() { return side; };
	GLuint getPifPafSize() const { return (GLuint)_piFpaF.size(); };
	void setSide(Animation::Direction sid) { side = sid; };
	std::vector<Projectile>& getpiFpaF() { return _piFpaF; };
	Projectile& getOnepiFpaF (GLuint index) { return _piFpaF[index]; };
	GLuint getPifPafTexture() { return _PifPafTexture->getID(); };
	GLuint getTexture() { return _texture->getID(); };
	Vec2d getPos() { return _position; };
	Vec2d& getCurrVelocity() { return _curVelocity; }
	Origin& getOrigin() { return _ori; };
	Vec2i getFrameIndex();
//================================================================
// Interakcja
//================================================================
	void consumeItem(const Item* item);
	bool TakeDamage(const Projectile& bullet)
	{
		m_health -= 20;
		return !(m_health > 0);
	};
	void updateAnimation(std::pair<Animation::Direction,Animation::Direction> dir, double deltaTime);
//================================================================
// Settery
//================================================================
	void setY(double y) 
	{ 
		_position._y = y;
		_ori.Update(false, _position);
	};
	void setX(double x) 
	{ 
		_position._x=x;
		_ori.Update(true, _position);
	};
	void setCurrVelocity(Vec2d& vel)
	{
		_curVelocity = vel;
	}
	void setCurrVelocityX(double x) { _curVelocity._x = x; }
	void setCurrVelocityY(double x) { _curVelocity._y = x; }
	void setCurrVelocity(double x, double y)
	{
		_curVelocity._x = x;
		_curVelocity._y = y;
	}

	//virtual void Bechaviour(const Character& player, double deltaTime) = 0;

protected:
	//Mozna skopiowaæ do Hero kwestia przekminy
	std::vector<Item*> _items;
	//Koniec do przekminiania

	//Coords
	Texture* _texture;
	Texture* _PifPafTexture;

	Origin _ori;
	//Weapons
	std::vector<Projectile> _piFpaF;
	//W ktora strone jest zwrocony
	Animation::Direction side;
	Animation _animation;
	//Do akceleracji strza³ów
	Vec2d _curVelocity;
};
#endif
