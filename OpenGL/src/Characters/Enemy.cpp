#include "Enemy.h"

Enemy::Enemy(double x, double y, double vel, std::string texturepath): Character(texturepath)
{
	posX = x;
	posY = y;
	m_speed = vel;
}

void Enemy::Bechaviour(const Character & player, double deltaTime)
{
	double px = player.posX;
	double py = player.posY;	
}

