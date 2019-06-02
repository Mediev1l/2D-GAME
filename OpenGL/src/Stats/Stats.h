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
	long m_health;
	long m_shield; // albo tylko hp
	long m_range;
	double m_speed;
	double m_att_speed;
	double m_damage;


public:
	Stats() :m_health(50), m_shield(0), m_range(25), m_speed(3.0), m_att_speed(1.0), m_damage(10.0) {};
	Stats(long h, long sh, long ran, double attsp, double mvm, double dmg) :m_health(h), m_shield(sh), m_range(ran), m_speed(mvm), m_att_speed(attsp), m_damage(dmg) {};
	long getHealth() const { return m_health; };
	long getShield() const { return m_shield; };
	long getRange() const { return m_range; };
	double getAttackSpeed() const { return m_att_speed; };
	double getMovementSpeed() const { return m_speed; };
	double getDamage() const { return m_damage; };


	long& getHealth() { return m_health; };
	long& getShield() { return m_shield; };
	long& getRange() { return m_range; };
	double& getAttackSpeed() { return m_att_speed; };
	double& getMovementSpeed() { return m_speed; };
	double& getDamage() { return m_damage; };

	void setRange(GLuint range) { m_range = range; };
	void setDamage(double d) { m_damage = d; };
	void setAttackSpeed(double sec) { m_att_speed = sec; };
	void setHealth(long h) { m_health = h; };
	void setSpeed(double s) { m_speed = s; };

};

#endif // !_Stats_H
