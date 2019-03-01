#ifndef MAP_H
#define MAP_H
#include <fstream>
#include <string>
#include <vector>
#include "Tile.h"
class Map
{
public:
	Map() = delete;
	Map(const Map&) = delete;
	Map(std::string FilePath, std::string BitmapsPath);
	~Map();

	unsigned int getTextureID(int nrelem) { return _Tiles[_TileIds[nrelem]].getID(); };
private:
	std::vector<int> _TileIds;
	std::vector<Tile> _Tiles;
};
#endif
