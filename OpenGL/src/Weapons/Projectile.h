


#ifndef _Projectile_H
#define _Projectile_H

#include "Basics/Coords.h"
#include "Renderer/Texture.h"
#include "Basics/Animation.h"

class Projectile : public Coords
{
public:
	enum Dir
	{
		NONE = -1,
		DOWN = 0,
		UP = 1,
		LEFT = 2,
		RIGHT = 3
	};
protected:
	double  size;
	double elapsedDistance;
	bool exist;
	Dir side;
	double origin = 0.2;
	Vec2d objVel;
	Animation _animation;
public:
	double Velocity;

	Projectile();
	Projectile(double size, double x, double y, double vel, double  distance, Projectile::Dir side, bool exist, Vec2d& objVel,GLuint nFrames);


	void UpdateAnimation(double dt) { _animation.UpdateAnimation({ Animation::DOWN,Animation::NONE },dt); }

	void setSize(double siz) { size = siz; };
	void setElapsedDistance(double elapsedDis) { elapsedDistance = elapsedDis; };
	void setExistance(bool exi) { exist = exi; };

	double getSize() { return size; };
	double getElapdedDistance() { return elapsedDistance; };
	bool getExistance() { return exist; };

	double getX()const { return _position._x; };
	double getY()const { return _position._y; };
	double getOrigin()const { return origin; };
	Vec2i getFrame() { return _animation.getAnimationIndex(); };
	Projectile::Dir getSide() { return side; };
	Vec2d& getObjVel() { return objVel; };


};
#endif // !_Projectile_H
