/*
Item

Obiekt odpowiedzialny za wszystkie przedmioty w grze

*/

#ifndef _Item_H
#define _Item_H

#include "Object.h"
#include "Stats.h"

class Item : public Object, Stats
{
protected:
	int m_id;
	std::string m_description;

public:
	Item();


};

#endif
