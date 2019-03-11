//================================================================
//= Klasa Odpowiadaj¹ca za pozycje na mapie
//= Prosty typ danych
//================================================================
#ifndef _Coords_H
#define _Coords_H
#include "Utility/Vec2.h"
class Coords
{
public:
	//================================================================
	//= Konstruktory
	//================================================================
	Coords() : _position(0.0, 0.0) {};
	Coords(double x, double y) : _position(x, y) {};
	Coords(const Vec2d& pos) : _position(pos) {};
	//================================================================
	//= Sk³adowe
	//================================================================
public:
	Vec2d _position;
};
#endif