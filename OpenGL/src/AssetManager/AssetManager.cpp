#include "AssetManager.h"



void AssetManager::LoadSprites()
{
	auto load = [&](std::string sName, std::string sFileName, bool transparent)
	{
		Texture* s = new Texture(sFileName,transparent);
		_mapSprites[sName] = s;
	};

	load("player", "res/Sprites/Player/issac.png",true);
	load("Basement", "res/Sprites/Map/Basement", false);
}

void AssetManager::LoadMaps()
{
	auto load = [&](Map* m)
	{
		_mapMaps[m->sName] = m;
	};

	load(new Map_Basement());
}

void AssetManager::LoadItems()
{
	auto load = [&](Item* i)
	{
		_mapItems[i->sName] = i;
	};
}

AssetManager::AssetManager()
{
}


AssetManager::~AssetManager()
{
}
