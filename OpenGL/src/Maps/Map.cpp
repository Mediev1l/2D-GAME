#include "Map.h"
using namespace std;
Map::Map(std::string TileIdsPath, std::string BitmapsPath)
{
	//Otwarcie pliku z Map¹
	ifstream TileIds(TileIdsPath);
	if (TileIds.good() == false)
	{
		throw std::runtime_error("Couldn't open the file: " + TileIdsPath);
	}

	//Wczytanie wymiarów mapy
	TileIds >> _width;
	TileIds >> _height;
	TileIds >> _nTextures;

	GLuint solid;
	GLuint textureID;
	//Initialize all Tiles
	for(GLuint y=0;y<_height;++y)
		for (GLuint x = 0; x < _width; ++x)
		{
			TileIds >> textureID;
			TileIds >> solid;
			_Tiles.emplace_back(solid == 0 ? false : true
								,solid==0?Tile::Content::Nothing:Tile::Content::Obstacle
								,x,y, textureID, _width);
		}

	//Initialize All Textures
	for (GLuint i = 0; i < _nTextures; ++i)
		_textures.emplace_back(BitmapsPath + to_string(i) + (i != _nTextures - 1 ? ".jpg":".png"), i!=_nTextures-1?false:true);
}
Map::~Map()
{
}

void Map::setTileContent(GLuint x, GLuint y, Tile::Content content)
{
	_Tiles[y*_width + x].setContent(content);
}
