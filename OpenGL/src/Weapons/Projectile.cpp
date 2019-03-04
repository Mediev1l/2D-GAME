#include "Projectile.h"

Projectile::Projectile()
	: size(1), Coords{0, 0, 10}, side(Projectile::NONE), elapsedDistance(0), exist(false)
{
}

Projectile::Projectile(double size, double x, double y, double vel, double  distance, Projectile::Dir side, bool exist)
	: size(size), Coords{ x, y, vel }, side (side), elapsedDistance(distance), exist(exist)
{
}
