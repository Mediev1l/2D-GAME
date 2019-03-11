#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H
#include <map>
#include "Maps/Map.h"
#include "Items/Item.h"
#include "Characters/Character.h"

class AssetManager
{
public:
	static AssetManager& Get()
	{
		static AssetManager me;
		return me;
	}

	AssetManager(const AssetManager& src) = delete;
	AssetManager& operator=(const AssetManager& src) = delete;

	Map* getMap(std::string name)
	{
		return _mapMaps[name];
	};

	Item* getItem(std::string name)
	{
		return _mapItems[name];
	};

	Texture* getSprite(std::string name)
	{
		return _mapSprites[name];
	};

	void LoadSprites();
	void LoadMaps();
	void LoadItems();

private:
	AssetManager();
	~AssetManager();

	std::map<std::string, Map*> _mapMaps;
	std::map<std::string, Item*> _mapItems;
	std::map<std::string, Texture*> _mapSprites;
};
#endif