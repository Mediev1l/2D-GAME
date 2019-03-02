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
	int solid;
	while (TileIds >> x)
	{
		TileIds >> solid;
		_TileIds.emplace_back(x,solid==0?false:true);
	}
	int numberofsprites = 11;
	for (int i = 0; i < numberofsprites; ++i)
	{
		_Tiles.emplace_back("res/Sprites/Map1/"+to_string(i)+".jpg",Get(i).second,false);
	}
	//std::cout<<"Id 1 kafelki mapy: "<<_Tiles[0].getID()<<'\n';
}

Map::~Map()
{
}

std::pair<int, bool>& Map::Get(int i)
{
	for (int j = 0; j < _TileIds.size(); ++j) if (_TileIds[j].first == i) return _TileIds[j];
	std::pair<int, bool> a(-1, false);
	return a;
}
