#include "DebugInfo.h"



DebugInfo::DebugInfo()
{
}


DebugInfo::~DebugInfo()
{
}

void DebugInfo::Init(std::vector<Character>& _characters)
{
	info.clear();
	for (size_t i = 0; i < _characters.size(); ++i)
	{
		info.emplace_back(
			&_characters[i].sName
			, &_characters[i]._position
			, &_characters[i].getHealth()
			, &_characters[i].getShield()
			, &_characters[i].getRange()
			, &_characters[i].getMovementSpeed()
			, &_characters[i].getAttackSpeed()
			, &_characters[i].getDamage()
			, _characters[i].getFrameIndex());
	}
	DrawClear();
}

void DebugInfo::Update(std::vector<Character>& _characters)
{
	for (size_t i = 0; i < info.size(); ++i)
	{
		bool jest = false;
		for (size_t j = 0; j < _characters.size(); ++j)
		{
			if (_characters[j].sName == *info[i].name) jest = true;
		}
		if (!jest)
		{
			info[i] = info[info.size() - 1];
			info.pop_back();
			i--;
			system("cls");
			DrawClear();
		}
	}

	for (size_t i = 0; i < _characters.size(); ++i)
	{
		//info[i].pos = _characters[i]._position;
		//info[i].health = _characters[i].getHealth();
		//info[i].shield = _characters[i].getShield();
		//info[i].speed = _characters[i].getMovementSpeed();
		//info[i].range = _characters[i].getRange();
		//info[i].att_speed = _characters[i].getAttackSpeed();
		//info[i].damage = _characters[i].getDamage();	
		info[i].anim = _characters[i].getFrameIndex();
	}
}

void DebugInfo::DrawClear()
{
	COORD localStart=cStart;
	COORD cY = cStart;
	//SetConsoleCursorPosition(hn, cStart);
	for (size_t i = 0; i < info.size(); ++i)
	{
		size_t startx = (i%3) * 30;

		localStart.X = startx;
		localStart.Y = cY.Y;
		SetConsoleCursorPosition(hn, localStart);
		//Wypisywanie poszczegolnych
			std::cout << std::setw(15) << std::setprecision(5) <<*(info[i].name);
			localStart.X = startx; localStart.Y += 1;
			SetConsoleCursorPosition(hn, localStart);

			std::cout<< std::setw(15) << "PosX: " << std::setw(1) << info[i].pos->_x;
			localStart.X = startx; localStart.Y += 1;
			SetConsoleCursorPosition(hn, localStart);

			std::cout << std::setw(15) << "PosY: " << std::setw(1) << info[i].pos->_y;
			localStart.X = startx; localStart.Y += 1;
			SetConsoleCursorPosition(hn, localStart);

			std::cout << std::setw(15) << "Health: " << std::setw(1) << *(info[i].health);
			localStart.X = startx; localStart.Y += 1;
			SetConsoleCursorPosition(hn, localStart);

			std::cout << std::setw(15) << "Shield: " << std::setw(1) << *(info[i].shield);
			localStart.X = startx; localStart.Y += 1;
			SetConsoleCursorPosition(hn, localStart);

			std::cout << std::setw(15) << "Range: " << std::setw(1) << *(info[i].range);
			localStart.X = startx; localStart.Y += 1;
			SetConsoleCursorPosition(hn, localStart);

			std::cout << std::setw(15) << "Speed: " << std::setw(1) << *(info[i].speed);
			localStart.X = startx; localStart.Y += 1;
			SetConsoleCursorPosition(hn, localStart);

			std::cout << std::setw(15) << "AttackSpeed: " << std::setw(1) << *(info[i].att_speed);
			localStart.X = startx; localStart.Y += 1;
			SetConsoleCursorPosition(hn, localStart);

			std::cout << std::setw(15) << "Dmg: " << std::setw(1) << *(info[i].damage);
			localStart.X = startx; localStart.Y += 1;
			SetConsoleCursorPosition(hn, localStart);

			std::cout << std::setw(15) << "Anim x,y: " << std::setw(1) << info[i].anim._x << " " << info[i].anim._y;

		if ((i + 1) % 3 == 0) cY.Y += 12;//?
	}
}

void DebugInfo::Draw()
{
	COORD localStart = cStart;
	COORD cY = cStart;
	//SetConsoleCursorPosition(hn, cStart);
	for (size_t i = 0; i < info.size(); ++i)
	{
		size_t startx = (i % 3) * 30 + 16;

		localStart.X = startx;
		localStart.Y = cY.Y;
		//SetConsoleCursorPosition(hn, localStart);
		//Wypisywanie poszczegolnych
		//std::cout << std::setw(15) << std::setprecision(5) << info[i].name;
		localStart.X = startx; localStart.Y += 1;
		SetConsoleCursorPosition(hn, localStart);

		std::cout<< std::setw(1) << info[i].pos->_x;
		localStart.X = startx; localStart.Y += 1;
		SetConsoleCursorPosition(hn, localStart);

		std::cout << std::setw(1) << info[i].pos->_y;
		localStart.X = startx; localStart.Y += 1;
		SetConsoleCursorPosition(hn, localStart);

		std::cout << std::setw(1) << *(info[i].health);
		localStart.X = startx; localStart.Y += 1;
		SetConsoleCursorPosition(hn, localStart);

		std::cout << std::setw(1) << *(info[i].shield);
		localStart.X = startx; localStart.Y += 1;
		SetConsoleCursorPosition(hn, localStart);

		std::cout <<  std::setw(1) << *(info[i].range);
		localStart.X = startx; localStart.Y += 1;
		SetConsoleCursorPosition(hn, localStart);

		std::cout <<  std::setw(1) << *(info[i].speed);
		localStart.X = startx; localStart.Y += 1;
		SetConsoleCursorPosition(hn, localStart);

		std::cout <<  std::setw(1) << *(info[i].att_speed);
		localStart.X = startx; localStart.Y += 1;
		SetConsoleCursorPosition(hn, localStart);

		std::cout << std::setw(1) << *(info[i].damage);
		localStart.X = startx; localStart.Y += 1;
		SetConsoleCursorPosition(hn, localStart);

		std::cout << std::setw(1) << info[i].anim._x << " " << info[i].anim._y;

		if ((i + 1) % 3 == 0) cY.Y += 12;//?
	}
}