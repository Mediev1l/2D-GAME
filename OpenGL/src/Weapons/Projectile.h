


#ifndef _Projectile_H
#define _Projectile_H

#include "Basics/Coords.h"
#include "Renderer/Texture.h"
#include "Basics/Animation.h"
#include "Basics/Origin.h"

class Projectile : public Coords
{
protected:
	double  size;
	double elapsedDistance;
	bool exist;
	Animation::Direction side;
	Origin _ori;
	Vec2d objVel;
	Animation _animation;
public:
	double Velocity;

	Projectile();
	Projectile(Vec2d OriSize, double x, double y, double vel, double  distance, Animation::Direction side, bool exist, Vec2d& objVel,GLuint nFrames);


	void UpdateAnimation(double dt) { _animation.UpdateAnimation({ Animation::DOWN,Animation::NONE },dt); }

	void setSize(double siz) { size = siz; };
	void setElapsedDistance(double elapsedDis) { elapsedDistance = elapsedDis; };
	void setExistance(bool exi) { exist = exi; };

	double getSize() { return size; };
	double getElapdedDistance() { return elapsedDistance; };
	bool getExistance() { return exist; };

	double getX()const { return _position._x; };
	double getY()const { return _position._y; };
	Origin& getOrigin() { return _ori; };
	Vec2i getFrame() { return _animation.getAnimationIndex(); };
	Animation::Direction getSide() { return side; };
	Vec2d& getObjVel() { return objVel; };


};
#endif // !_Projectile_H
