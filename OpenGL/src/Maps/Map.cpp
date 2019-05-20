#include "Map.h"
#include "AssetManager/AssetManager.h"
using namespace std;
Map::Map()
{
}
Map::~Map()
{
}

void Map::Create(std::string name, std::string lvldatapath, Texture* text)
{
	sName = name;
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
	TileIds >> textwidth;
	TileIds >> textheight;
	
	GLuint solid;
	GLuint textureNumber;
	//Initialize all Tiles
	for (GLuint y = 0; y < _height; ++y)
		for (GLuint x = 0; x < _width; ++x)
		{
			TileIds >> textureNumber;
			TileIds >> solid;
			_Tiles.emplace_back(solid == 0 ? false : true, x, y, textureNumber,Vec2d(1.0,1.0));
		}

	//Initialize Texture
	_texture = text;
	_texture->setWidth(textwidth);
	_texture->setHeight(textheight);
	_texture->setnSprites(nTextures);
}

void Map::LoadLevel(std::vector<std::pair<int, bool>> lvl)
{
	_Tiles.clear();
	for (GLuint y = 0; y < _height; ++y)
		for (GLuint x = 0; x < _width; ++x)
			_Tiles.emplace_back(false, x, y, 1, Vec2d(1.0, 1.0));
	//Sprawdzic to
	for(GLuint y=0;y<_height;++y)
		for (GLuint x = 0; x < _width; ++x)
		{
			//GLuint index = (y - 1)*(_width - 2) + (x - 1);
			_Tiles[y*_width + x].setTextureIDandSolid(lvl[y*_width + x].first,lvl[y*_width + x].second);
		}
}

Map_Basement::Map_Basement()
{
	Create("Basement", "res/Data/Map/Basement.txt", AssetManager::Get().getSprite("Basement2"));
}
