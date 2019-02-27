#ifndef _TILE_H
#define _TILE_H
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION

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