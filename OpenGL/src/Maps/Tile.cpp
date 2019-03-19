#include "Tile.h"



Tile::Tile(bool solid, GLuint x, GLuint y, GLuint texture, Vec2d OriSize)
	:
	 _solid(solid)
	,_position((double)x,(double)y)
	,_textureNumber(texture)
	,_ori(4, OriSize,_position)
	,_vertexs()
{
	//Dla wielok¹tów 
	/*float fTheta = 3.14159f * 2.0f / 5.0f;
	s1.pos = { 100, 100 };
	s1.angle = 0.0f;
	for (int i = 0; i < 5; i++)
	{
		s1.o.push_back({ 30.0f * cosf(fTheta * i), 30.0f * sinf(fTheta * i) });

	}*/
}

Tile::Tile(bool solid, Vec2d pos, GLuint texture, Vec2d OriSize)
	:
	 Tile(solid,(GLuint)pos._x, (GLuint)pos._y,texture,OriSize)
	{}

Tile::~Tile()
{
}

void Tile::UpdateVertexs(bool ox)
{
	_ori.Update(ox, _position);
}
