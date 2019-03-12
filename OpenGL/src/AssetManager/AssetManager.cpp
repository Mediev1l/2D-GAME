#include "AssetManager.h"


void AssetManager::LoadSprites()
{
	auto load = [&](std::string sName, std::string sFileName, bool transparent)
	{
		Texture* s = new Texture(sFileName,transparent);
		_mapSprites[sName] = s;
	};

	//Dynamics
	load("player", "res/Sprites/Player/player.png",true);
	load("player2", "res/Sprites/Player/player2.png",true);
	load("pifpaf", "res/Sprites/Tears/basic_tear.png", true);
	load("skelly", "res/Sprites/Enemies/Skelly/skelly.png", true);
	load("skelly2", "res/Sprites/Enemies/Skelly/skeleton.png", true);
	load("zombie", "res/Sprites/Enemies/Zombie/zombie.png", true);
	load("zombie2", "res/Sprites/Enemies/Zombie/zombie2.png", true);
	load("SpeedBoots", "res/Sprites/Items/SpeedBoots.png", true);

	//Map
	load("Basement", "res/Sprites/Map/Basement/Basement.jpg", false);
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

	load(new SpeedBoots());
}

AssetManager::AssetManager()
{
}


AssetManager::~AssetManager()
{
}
