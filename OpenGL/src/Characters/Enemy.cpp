#include "Enemy.h"

Enemy::Enemy(double x, double y, double vel,double size, std::string texturepath, std::string PifPafTexturePath)
	:
	Character(texturepath, PifPafTexturePath,x,y,size)
{
	m_speed = vel;
}

void Enemy::Bechaviour(const Character & player, double deltaTime)
{
	//double px = player.posX;
	//double py = player.posY;	
}

