/*
Stats

Klasa ze wszystkimi statystykami gracza jak i przeciwnikow
*/

#ifndef _Stats_H
#define _Stats_H

class Stats
{
protected:
	int m_health;
	int m_shield; // albo tylko hp
	double m_speed;
	double m_att_speed;
	double m_damage;
public:
	Stats();	
	int getHealth()const { return m_health; };
	int getShield()const { return m_shield; };
	double getAttackSpeed()const { return m_att_speed; };
	double getMovementSpeed()const { return m_speed; };
	double getDamage()const { return m_damage; };

};

#endif // !_Stats_H
