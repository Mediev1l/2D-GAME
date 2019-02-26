#include "Map.h"
using namespace std;
Map::Map(std::string TileIdsPath, std::string BitmapsPath)
{
	ifstream TileIds(TileIdsPath);
	if (TileIds.good() == false)
	{
		throw std::runtime_error("Couldn't open the file: " + TileIdsPath);
	}

	int x;
	while (TileIds >> x)
	{
		_TileIds.push_back(x);
	}
	int numberofsprites = 10;
	for (int i = 0; i < numberofsprites; ++i)
	{
		_Tiles.emplace_back(BitmapsPath+"/"+"wooden.jpg"+".jpg");
	}
}

Map::~Map()
{
}
