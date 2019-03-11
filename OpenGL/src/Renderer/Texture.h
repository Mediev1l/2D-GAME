#ifndef TEXTURE_H
#define TEXTURE_H
#include <stb_image.h>
#include <GL/glew.h>
#include <string>

class Texture
{
public:
	Texture();
	Texture(const std::string& Path, bool transparent);
	Texture(const std::string& Path, bool transparent, GLuint pwidth, GLuint pheight, GLuint nSprites);
	~Texture();

	//Gettery
	GLuint getID() { return ID; };
	double getWidth() { return _width; };
	double getHeight() { return _height; };
	GLuint getnSprites() { return _nSprites; };

	//Settery
	void setID(GLuint x) { ID = x; };
	void setWidth(GLuint x) { _width=x; };
	void setHeight(GLuint x) { _height=x; };
	void setnSprites(GLuint x) {  _nSprites=x; };
private:
	GLuint ID;
	GLuint _width;
	GLuint _height;
	GLuint _nSprites;
};

#endif