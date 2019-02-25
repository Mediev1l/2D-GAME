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
	float m_speed;
	float m_att_speed;
	float m_damage;
	float m_size;
public:
	Stats();	

};

#endif // !_Stats_H
