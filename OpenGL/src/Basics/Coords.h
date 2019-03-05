/*
Coords

Prosty obiekt z koordynatami

*/


#ifndef _Coords_H
#define _Coords_H
#include"Utility/Vec2.h"
struct Coords
{
	Coords()
		:
		_position()
		, Velocity(0)
	{};
	Coords(double x, double y, double vel)
		:
		_position(x, y)
		, Velocity(vel) 
	{};
public:
	Vec2d _position;
	double Velocity;
};

#endif