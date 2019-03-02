#ifndef MAP_H
#define MAP_H
#include <fstream>
#include <string>
#include <vector>
#include "Tile.h"
class Map
{
public:
	Map()= delete;
	Map(const Map&) = delete;
	Map(std::string FilePath, std::string BitmapsPath);
	~Map();

	unsigned int getTextureID(int nrelem) { return _Tiles[_TileIds[nrelem].first].getID(); };
	//HARDKODOWANA 10 DO POPRAWY !
	bool isObstacle(int x, int y) { return _Tiles[_TileIds[y * 10 + x].first].isObstacle(); };
	
private:
	std::vector<std::pair<int,bool>> _TileIds;
	std::vector<Tile> _Tiles;

private:
	std::pair<int, bool>& Get(int i);
};
#endif
