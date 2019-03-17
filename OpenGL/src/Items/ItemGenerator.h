

#ifndef _Item_Generator_H
#define _Item_Generator_H

#include <time.h>

#include "AssetManager/AssetManager.h"

class ItemGenerator
{
private:

	std::vector<Item*> _items;
	std::vector<std::string> _used;

public:

	ItemGenerator() { srand((GLuint)time(NULL)); };
	~ItemGenerator() {};

	ItemGenerator(const ItemGenerator& cpy) = delete;
	void operator = (const ItemGenerator& cpy) = delete;

	std::vector<Item*> getItems() { return _items; };
	void GenerateItem(bool unique, GLuint x, GLuint y);



};

#endif
