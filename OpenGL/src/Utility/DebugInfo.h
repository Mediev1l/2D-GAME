#ifndef DEBUHI_H
#define DEBUGI_H

//Our libs
#include "Characters/Character.h"
#include "Utility/Vec2.h"
#include <GL/glew.h>

//Win Libs;
#include <Windows.h>
#include <iostream>
#include <iomanip>

class DebugInfo
{
public:
	DebugInfo();
	~DebugInfo();
public:
	void Init(std::vector<Character>& _characters);
	void Update(std::vector<Character>& _characters);
	void DrawClear();
	void Draw();
private:
	struct CharInfo
	{
		CharInfo(std::string* n, Vec2d* p, long* h, long* sh, long* ran, double* spd, double* atspd, double* dmg, Vec2i a)
			:
			name(n), pos(p), health(h),shield(sh),range(ran),speed(spd),att_speed(atspd),damage(dmg), anim(a)
		{};
		std::string* name;
		Vec2d* pos;
		long* health;
		long* shield; // albo tylko hp
		long* range;
		double* speed;
		double* att_speed;
		double* damage;
		Vec2i anim;
		std::vector<std::string> vItems;
	};
	std::vector<CharInfo> info;
	HANDLE hn = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cStart = {0,4};
	COORD cCurrent;
};

#endif
