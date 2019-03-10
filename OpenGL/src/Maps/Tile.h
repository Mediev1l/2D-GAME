#ifndef _TILE_H
#define _TILE_H
#include <vector>
#include "Shaders/Shader.h"
#include "Renderer/Texture.h"
#include "Utility/Vec2.h"

class Tile
{
public:
	enum Content
	{
		Nothing = 0,
		Obstacle = 1,
		Item = 2,
		Character = 3,
		Doors = 4,
		Player = 5
	};
	Tile() = delete;
	Tile(bool solid,Content con, GLuint x, GLuint y, GLuint texture, double size);
	//Tile(bool solid,Content con, double x, double y, GLuint texture, double size);
	Tile(bool solid,Content con, Vec2d pos, GLuint texture, double size);
	~Tile();

	//================================================================
	//= Podstawowe Gettery
	//================================================================
	GLuint getTextureID() { return _textureID; };
	Content getContent() { return _content; };
	bool isSolid() { return _solid; };
	Vec2d& getPos() { return _position; };
	GLuint getVertexCount() 
	{ 
		return (GLuint)_vertexs.size(); 
	};
	Vec2d& getVertex(GLuint x) 
	{ 
		return _vertexs[x];
	};
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

	void setTextureIDandSolid(GLuint x, bool sol) 
	{ 
		_textureID = x;
		_solid = sol;
		_content = sol ? Content::Obstacle : Content::Nothing;
	};

	//================================================================
	//= Utility
	//================================================================
	void UpdateVertexs(bool ox);
	double getOrigin()const { return _size; };
private:
	GLuint _textureID;
	Vec2d _position;
	std::vector<Vec2d> _vertexs;
	double _size;
	bool _solid;
	Content _content;
};
#endif