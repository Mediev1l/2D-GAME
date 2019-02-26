#ifndef TILE_H
#define TILE_H
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include "Shader.h"

class Tile
{
public:
	Tile() = delete;
	Tile(std::string Path,Shader& shader);
	~Tile();
	unsigned int getID() { return id; };
private:
	unsigned int id;
};
#endif