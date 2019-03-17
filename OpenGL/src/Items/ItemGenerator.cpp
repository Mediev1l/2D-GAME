#include "ItemGenerator.h"

void ItemGenerator::GenerateItem(bool unique, GLuint x, GLuint y)
{
	auto it = AssetManager::Get().getItems().begin();
	auto items = AssetManager::Get().getItems();
	std::vector<std::string>::iterator usedit;


	
	if (unique != true)
	{
		std::advance(it, rand() % items.size());
		_items.emplace_back(AssetManager::Get().getItem(it->first));

		
		usedit = std::find(_used.begin(), _used.end(), it->first);
		if (usedit == _used.end())
		{
			_used.push_back(it->first);
		}

		_items[_items.size() - 1]->setX(x);
		_items[_items.size() - 1]->setY(y);


	}
	else
	{

		while (_used.size() != items.size())
		{
			std::advance(it, rand() % items.size());

			usedit = std::find(_used.begin(), _used.end(), it->first);

			if (usedit == _used.end())
			{
				_items.emplace_back(AssetManager::Get().getItem(it->first));
				_used.push_back(it->first);
				_items[_items.size() - 1]->setX(x);
				_items[_items.size() - 1]->setY(y);
				break;
			}



		}
	}
	
	
}
