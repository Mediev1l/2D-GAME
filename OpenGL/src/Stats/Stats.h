/*
Stats

Klasa ze wszystkimi statystykami gracza jak i przeciwnikow
*/

#ifndef _Stats_H
#define _Stats_H

#include "GL/glew.h"


class Stats
{
protected:
	GLuint m_health;
	GLuint m_shield; // albo tylko hp
	GLuint m_range;
	double m_speed;
	double m_att_speed;
	double m_damage;


public:
	Stats();	
	GLuint getHealth() const { return m_health; };
	GLuint getShield() const { return m_shield; };
	GLuint getRange() const { return m_range; };
	double getAttackSpeed() const { return m_att_speed; };
	double getMovementSpeed() const { return m_speed; };
	double getDamage() const { return m_damage; };

	void setRange(GLuint range) { m_range = range; };

};

#endif // !_Stats_H
