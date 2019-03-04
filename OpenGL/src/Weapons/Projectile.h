


#ifndef _Projectile_H
#define _Projectile_H

#include "Basics/Coords.h"
#include "Renderer/Texture.h"

class Projectile : public Coords
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
protected:
	double  size;
	double elapsedDistance;
	bool exist;
	Dir side;
public:


	Projectile();
	Projectile(double size, double x, double y, double vel, double  distance, Projectile::Dir side, bool exist);


	void setSize(double siz) { size = siz; };
	void setElapsedDistance(double elapDis) { elapsedDistance = elapDis; };
	void setExistance(bool exi) { exist = exi; };

	double getSize() { return size; };
	double getElapdedDistance() { return elapsedDistance; };
	bool getExistance() { return exist; };

	Projectile::Dir getSide() { return side; };


};
#endif // !_Projectile_H
