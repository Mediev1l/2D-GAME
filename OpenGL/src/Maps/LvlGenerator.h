#ifndef LVLGEN_H
#define LVLGEN_H
#include <fstream>
#include <vector>
#include <ctime>
#include <random>
#include <GL/glew.h>

#include "Map.h"
#include "Characters/Enemy.h"
#include "Utility/Enums.h"
#include "Utility/Bar.h"

class LvlGenerator
{
public:
	LvlGenerator(std::string BlockListPath);
	~LvlGenerator();
	std::vector<std::pair<int, bool>> generateLevel(Map* map, Difficulty diff, Scenario s);
	void PopulateDynamics(std::vector<Character>& ch, Difficulty diff, Scenario s);
	void AddBar(Bar& bar);

	bool Doors(GLuint x, GLuint y)
	{
		for (GLuint i = 0; i < 6; i += 2)
		{
			if (x == doorpos[i] || y == doorpos[i + 1]) return true;
		}
		return false;
	};
private:
	std::vector<std::pair<int, bool>> _leveldata;
	GLuint doorpos[6];
	std::random_device device;
	std::mt19937 eng;
	//std::uniform_int_distribution<GLuint> dist;
	GLuint width;
	GLuint height;
	Bar* bar;
};
#endif
