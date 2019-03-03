#include "Tile.h"



Tile::Tile(bool solid, Content con, GLuint x, GLuint y, GLuint texture, GLuint& w)
	:
	 _solid(solid)
	,_content(con)
	,_tileID(y*w+x)
	,_textureID(texture)
{
	
}

Tile::~Tile()
{
}
