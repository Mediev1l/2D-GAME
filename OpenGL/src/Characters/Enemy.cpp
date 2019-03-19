#include "Enemy.h"

Enemy::Enemy(std::string name, double x, double y, double vel, Vec2d OriSize, GLuint nFrames)
	:
	Character(name,x,y,OriSize,nFrames)
{
	m_speed = vel;
}

void Enemy::Bechaviour(const Character & player, double deltaTime)
{
	//double px = player.posX;
	//double py = player.posY;	
}

