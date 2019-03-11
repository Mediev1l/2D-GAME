#ifndef _TILE_H
#define _TILE_H
#include <vector>
#include "Shaders/Shader.h"
#include "Renderer/Texture.h"
#include "Utility/Vec2.h"
#include "Basics/Origin.h"

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
	Tile(bool solid, GLuint x, GLuint y, GLuint texture, double origin);
	Tile(bool solid, Vec2d pos, GLuint texture, double origin);
	~Tile();

	//================================================================
	//= Podstawowe Gettery
	//================================================================
	GLuint getTextureNumber() { return _textureNumber; };
	//Content getContent() { return _content; };
	bool GetSolid() { return _solid; };
	Vec2d& GetPos() { return _position; };
	GLuint GetVertexCount() 
	{ 
		return _ori.getVertexCount();
	};
	Vec2d& getVertex(GLuint x) 
	{ 
		return _ori.getVertex(x);
	};
	//================================================================
	//= Podstawowe Settery
	//================================================================
	/*void setContent(Content content) 
	{
		_content = content;
		if (content == Item)_solid = true; 
		if (content == Obstacle)_solid = true; 
		if (content == Nothing)_solid = false;
	};*/

	void setTextureIDandSolid(GLuint x, bool sol) 
	{ 
		_textureNumber = x;
		_solid = sol;
		//_content = sol ? Content::Obstacle : Content::Nothing;
	};

	//================================================================
	//= Utility
	//================================================================
	void UpdateVertexs(bool ox);
	Origin& getOrigin() { return _ori; };
private:
	GLuint _textureNumber;
	Vec2d _position;
	std::vector<Vec2d> _vertexs;
	Origin _ori;
	bool _solid;
	//Content _content;
};
#endif