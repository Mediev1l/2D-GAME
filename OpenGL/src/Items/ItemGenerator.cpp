#include "ItemGenerator.h"

void ItemGenerator::GenerateItem(GLuint x, GLuint y)
{
	auto itStart = AssetManager::Get().getItems().begin();
	auto itEnd = AssetManager::Get().getItems().end();
	auto items = AssetManager::Get().getItems();
	std::vector<std::string>::iterator usedit;


		while (_used.size() != items.size())
		{
			int random = rand() % items.size();
			int dist = (int)std::distance(itStart, AssetManager::Get().getItems().end());
			if (dist == 1)
				itStart = AssetManager::Get().getItems().begin();
			if (dist - random > 0 || dist == 6)
			{
				std::advance(itStart, random);
				usedit = std::find(_used.begin(), _used.end(), itStart->first);
		
				if (usedit == _used.end())
				{
					_items.emplace_back(AssetManager::Get().getItem(itStart->first));
					_used.emplace_back(itStart->first);
					_items[_items.size() - 1]->setX((float)x);
					_items[_items.size() - 1]->setY((float)y);
					break;
				}

			}
		}
	
}

void ItemGenerator::Clear()
{
	if(_items.size()>0) _items[_items.size() - 1]->setOnMap(false);
}
