#ifndef _TILE_H
#define _TILE_H
#include "Shaders/Shader.h"
#include "Renderer/Texture.h"


class Tile
{
public:
	enum Content
	{
		Nothing = 0,
		Obstacle = 1,
		Item = 2
	};
	Tile() = delete;
	Tile(bool solid,Content con, GLuint x, GLuint y, GLuint texture, GLuint& w);
	~Tile();

	//================================================================
	//= Podstawowe Gettery
	//================================================================
	GLuint getTextureID() { return _textureID; };
	Content getContent() { return _content; };
	bool isSolid() { return _solid; }

	//================================================================
	//= Podstawowe Settery
	//================================================================
	void setContent(Content content) 
	{
		_content = content;
		if (content == Item)_solid = true; 
		if (content == Obstacle)_solid = true; 
		if (content == Nothing)_solid = false;
	};

private:
	GLuint _textureID;
	GLuint _tileID;
	bool _solid;
	Content _content;
};
#endif