#include "Map.h"
using namespace std;
Map::Map()
{
}
Map::~Map()
{
}

void Map::Create(std::string name, std::string lvldatapath, Texture* text)
{
	//Otwarcie pliku z Map¹
	std::ifstream TileIds(lvldatapath);
	if (TileIds.good() == false)
	{
		throw std::runtime_error("Couldn't open the file: " + lvldatapath);
	}

	GLuint nTextures;
	GLuint textwidth;
	GLuint textheight;
	//Wczytanie wymiarów mapy
	TileIds >> _width;
	TileIds >> _height;
	TileIds >> nTextures;
	
	GLuint solid;
	GLuint textureNumber;
	//Initialize all Tiles
	for (GLuint y = 0; y < _height; ++y)
		for (GLuint x = 0; x < _width; ++x)
		{
			TileIds >> textureNumber;
			TileIds >> solid;
			_Tiles.emplace_back(solid == 0 ? false : true, x, y, textureNumber, 1.0);
		}

	//Initialize Texture
	_texture = text;
	_texture->setWidth(textwidth);
	_texture->setHeight(textheight);
	_texture->setnSprites(nTextures);
}

void Map::LoadLevel(std::vector<std::pair<int, bool>> lvl)
{
	//Sprawdzic to
	for(GLuint y=1;y<_height-1;++y)
		for (GLuint x = 1; x < _width - 1; ++x)
		{
			GLuint index = (y - 1)*(_width - 2) + (x - 1);
			_Tiles[y*_width + x].setTextureIDandSolid(lvl[index].first,lvl[index].second);
		}
}

Map_Basement::Map_Basement()
{
	Create("Basement", "res/Data/Map/Basement.txt", AssetManager::Get().getSprite("Basement"));
}
