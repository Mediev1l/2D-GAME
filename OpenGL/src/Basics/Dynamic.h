/*
Obiekt

Klasa odpowiedzialna  za wszystkie obiekty ktore bedziemy wyswietlali na ekran

*/

#ifndef _Object_H
#define _Object_H

#include <string>
#include "Coords.h"

class Dynamic : public Coords
{
public:
	std::string sName;
	double m_size;
public:
	Dynamic(): sName(""), m_size(0.0) {};
	Dynamic(std::string name, double x, double y) : Coords(x, y), sName(name), m_size(1.0) {};
};

#endif 
