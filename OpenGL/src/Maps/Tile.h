#ifndef _TILE_H
#define _TILE_H
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include "Shaders/Shader.h"
#define STB_IMAGE_IMPLEMENTATION

class Tile
{
public:
	Tile() = delete;
	Tile(std::string Path,bool solid, bool transparent);
	~Tile();
	unsigned int getID() { return id; };
	bool isObstacle() { return obstacle; }
private:
	unsigned int id;
	bool obstacle;
};
#endif