#ifndef TEXTURE_H
#define TEXTURE_H
#include <stb_image.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class Texture
{
public:
	Texture();
	Texture(const std::string& Path, bool transparent);
	~Texture();

	GLuint getID() { return ID; };
private:
	GLuint ID;
};

#endif