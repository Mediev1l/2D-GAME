#ifndef TILE_H
#define TILE_H
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <GLFW/glfw3.h>
#include <GL/glew.h>
class Tile
{
public:
	Tile() = delete;
	Tile(std::string Path);
	~Tile();
private:
	unsigned int id;
};
#endif