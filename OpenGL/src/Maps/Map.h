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
private:
	std::vector<int> _TileIds;
	//int _width;
	//int _height;
	std::vector<Tile> _Tiles;
};
#endif
