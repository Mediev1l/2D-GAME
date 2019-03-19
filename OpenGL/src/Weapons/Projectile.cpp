#include "Projectile.h"

Projectile::Projectile()
	: 
	 size(1)
	, Coords{0, 0}
	, side(Animation::Direction::NONE)
	, elapsedDistance(0), exist(false)
	, Velocity(10)
	, _animation(9,1.0/9)
{
}

Projectile::Projectile(Vec2d OriSize, double x, double y, double vel, double  distance, Animation::Direction side, bool exist, Vec2d &objVel, GLuint nFrames)
	: 
	 size(size)
	, Coords{ x, y}
	, side (side)
	, elapsedDistance(distance)
	, exist(exist)
	, objVel(objVel)
	, Velocity(vel)
	,_animation(nFrames,1.0/nFrames)
	, _ori(4, OriSize, {x,y})
{
}
