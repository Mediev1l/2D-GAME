#include "Tile.h"



Tile::Tile(bool solid, Content con, GLuint x, GLuint y, GLuint texture, double size)
	:
	 _solid(solid)
	,_content(con)
	,_position(x,y)
	,_textureID(texture)
	,_size(size)
	,_vertexs()
{
	//Dla wielokątów 
	/*float fTheta = 3.14159f * 2.0f / 5.0f;
	s1.pos = { 100, 100 };
	s1.angle = 0.0f;
	for (int i = 0; i < 5; i++)
	{
		s1.o.push_back({ 30.0f * cosf(fTheta * i), 30.0f * sinf(fTheta * i) });

	}*/

	double half = _size / 2;
	_vertexs.emplace_back(_position.getX() - half,_position.getY()-half);
	_vertexs.emplace_back(_position.getX() + half,_position.getY()-half);
	_vertexs.emplace_back(_position.getX() + half,_position.getY()+half);
	_vertexs.emplace_back(_position.getX() - half,_position.getY()+half);
}

Tile::Tile(bool solid, Content con, Vec2d pos, GLuint texture, double size)
	:
	 _solid(solid)
	, _content(con)
	, _position(pos)
	, _textureID(texture)
	, _size(size)
	, _vertexs()
{
	double half = _size / 2;
	_vertexs.emplace_back(_position.getX() - half, _position.getY() - half);
	_vertexs.emplace_back(_position.getX() + half, _position.getY() - half);
	_vertexs.emplace_back(_position.getX() + half, _position.getY() + half);
	_vertexs.emplace_back(_position.getX() - half, _position.getY() + half);
}

Tile::~Tile()
{
}

void Tile::UpdateVertexs(bool ox)
{
	if (ox)
	{
		_vertexs[0].setX(_position.getX() - _size / 2.0);
		_vertexs[1].setX(_position.getX() + _size / 2.0);
		_vertexs[2].setX(_position.getX() + _size / 2.0);
		_vertexs[3].setX(_position.getX() - _size / 2.0);
	}
	else
	{
		_vertexs[0].setY(_position.getY() - _size / 2.0);
		_vertexs[1].setY(_position.getY() - _size / 2.0);
		_vertexs[2].setY(_position.getY() + _size / 2.0);
		_vertexs[3].setY(_position.getY() + _size / 2.0);
	}
}
