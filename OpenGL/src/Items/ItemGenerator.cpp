#include "ItemGenerator.h"

void ItemGenerator::GenerateItem(GLuint x, GLuint y, bool unique)
{
	auto itStart = AssetManager::Get().getItems().begin();
	auto itEnd = AssetManager::Get().getItems().end();
	auto items = AssetManager::Get().getItems();
	std::vector<std::string>::iterator usedit;


	
	if (unique != true)
	{
		std::advance(itStart, rand() % items.size());

		_items.emplace_back(AssetManager::Get().getItem(itStart->first));

		
		if (itStart == itEnd) itStart = AssetManager::Get().getItems().begin();

		usedit = std::find(_used.begin(), _used.end(), itStart->first);

		if (usedit == _used.end()) _used.emplace_back(itStart->first);

		_items[_items.size() - 1]->setX(x);
		_items[_items.size() - 1]->setY(y);


	}
	else
	{

		while (_used.size() != items.size())
		{
			std::advance(itStart, rand() % items.size());

			if(itStart == itEnd) itStart = AssetManager::Get().getItems().begin();

			usedit = std::find(_used.begin(), _used.end(), itStart->first);

			if (usedit == _used.end())
			{
				_items.emplace_back(AssetManager::Get().getItem(itStart->first));
				_used.emplace_back(itStart->first);
				_items[_items.size() - 1]->setX(x);
				_items[_items.size() - 1]->setY(y);
				break;
			}



		}
	}
	
	
}
