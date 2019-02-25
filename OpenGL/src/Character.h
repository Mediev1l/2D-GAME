/*
Character

Obiekt odpowiadajacy za Postac (Glowny Bohater)

// tu jest b³¹d bo po tym obiekcie powinna dziedziczyc klasa enemy i hero 
// + nazwac to inaczej

*/

#ifndef _Character_H
#define _Character_H

#include "Coords.h"
#include "Stats.h"
#include "Skill.h"

class Character : public Coords, Stats, Skill
{
protected:
	

};

#endif
