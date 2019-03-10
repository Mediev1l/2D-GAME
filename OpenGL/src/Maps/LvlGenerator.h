#ifndef LVLGEN_H
#define LVLGEN_H
#include <fstream>
#include <vector>
#include <ctime>
#include <GL/glew.h>
class LvlGenerator
{
public:
	LvlGenerator(std::string BlockListPath);
	~LvlGenerator();
	std::vector<std::pair<int, bool>> generateLevel(GLuint width, GLuint height);
private:
	std::vector<std::pair<int, bool>> _leveldata;
};
#endif
