/*
Obiekt

Klasa odpowiedzialna  za wszystkie obiekty ktore bedziemy wyswietlali na ekran

*/

#ifndef _Object_H
#define _Object_H

#include <string>
#include "Coords.h"

class Object : public Coords
{
protected:
	std::string m_name;
	int m_size;
public:
	Object() {};


};

#endif 
