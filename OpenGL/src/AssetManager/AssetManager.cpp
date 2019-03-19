#include "AssetManager.h"


void AssetManager::LoadSprites()
{
	auto load = [&](std::string sName, std::string sFileName, bool transparent)
	{
		Texture* s = new Texture(sFileName,transparent);
		_mapSprites[sName] = s;
	};

	//Dynamics
	//load("player", "res/Sprites/Player/player.png",true);
	//load("player2", "res/Sprites/Player/player2.png",true);
	load("player3", "res/Sprites/Player/player3.png",true);
	load("obj", "res/Sprites/Objects/objectsheet.png",true);
	load("pifpaf", "res/Sprites/Tears/basic_tear.png", true);
	load("pifpafsheet", "res/Sprites/Tears/tearsheet.png", true);
	load("skelly", "res/Sprites/Enemies/Skelly/skelly.png", true);
	load("skelly2", "res/Sprites/Enemies/Skelly/skeleton.png", true);
	load("zombie", "res/Sprites/Enemies/Zombie/zombie.png", true);
	load("zombie2", "res/Sprites/Enemies/Zombie/zombie2.png", true);
	load("SpeedBoots", "res/Sprites/Items/SpeedBoots.png", true);
	load("BMW", "res/Sprites/Items/BMW.png", true);

	//Map
	load("Basement", "res/Sprites/Map/Basement/Basement.jpg", false);
	load("Basement2", "res/Sprites/Map/Basement/basementNew.png", true);
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
	load(new  BMW());
}

AssetManager::AssetManager()
{
}


AssetManager::~AssetManager()
{
}
