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
	load("player", "res/Sprites/Player/player.png",true);
	load("obj", "res/Sprites/Objects/objectsheet.png",true);
	load("pifpaf", "res/Sprites/Tears/basic_tear.png", true);
	load("pifpafsheet", "res/Sprites/Tears/tearsheet.png", true);
	load("skelly", "res/Sprites/Enemies/Skelly/skelly.png", true);
	load("skelly2", "res/Sprites/Enemies/Skelly/skeleton.png", true);
	load("boss", "res/Sprites/Enemies/Boss/boss.png", true);
	load("bae", "res/Sprites/Enemies/Bae/bae.png", true);
	load("boy", "res/Sprites/Enemies/Boy/boy.png", true);
	load("zombie", "res/Sprites/Enemies/Zombie/zombie.png", true);
	load("zombie2", "res/Sprites/Enemies/Zombie/zombie2.png", true);
	load("SpeedBoots", "res/Sprites/Items/SpeedBoots.png", true);
	load("Menu1", "res/Sprites/Others/Menu1.png", false);
	load("Menu2", "res/Sprites/Others/Menu2.png", false);
	load("Menu3", "res/Sprites/Others/Menu3.png", false);
	load("Menu4", "res/Sprites/Others/Menu4.png", false);
	load("Menu5", "res/Sprites/Others/Menu5.png", false);
	load("Menu6", "res/Sprites/Others/Menu6.png", false);
	load("Menu7", "res/Sprites/Others/Menu7.png", false);
	load("Menu8", "res/Sprites/Others/Menu8.png", false);
	load("Menu9", "res/Sprites/Others/Menu9.png", false);
	load("Menu10", "res/Sprites/Others/Menu10.png", false);
	load("Menu11", "res/Sprites/Others/Menu11.png", false);
	load("Menu12", "res/Sprites/Others/Menu12.png", false);
	load("Menu13", "res/Sprites/Others/Menu13.png", false);
	load("Menu14", "res/Sprites/Others/Menu14.png", false);
	load("hp", "res/Sprites/Others/Bar.png", false);
	load("frame", "res/Sprites/Others/frame.png", true);
	load("items", "res/Sprites/Items/items.png", true);
	load("Font", "res/Sprites/Font/Font.png", true);

	//Map
	//load("Basement", "res/Sprites/Map/Basement/Basement.jpg", false);
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
	load(new Yamaha());
	load(new Wfis());
	load(new Dzban());
	load(new Cpp());
}

AssetManager::AssetManager()
{
}


AssetManager::~AssetManager()
{
}
