#include "Item.h"

Item::Item(const std::string & TexturePath,const std::string& ItemPath, size_t itemID)
	: texture(TexturePath, false, true), id(itemID), Stats()
{
	std::fstream itemFile;
	std::string text;

	itemFile.open(ItemPath + "item_" + std::to_string(itemID) + ".txt");

	if (!itemFile.good())
		std::cerr << "Couldnt load the file";
	

	// Na razie na sztywno || do zmiany
	std::getline(itemFile, text);
	id = stoi(text);

	std::getline(itemFile, text);
	m_name = text;

	std::getline(itemFile, text);
	description = text;

	std::getline(itemFile, text);
	m_health = stoi(text);

	std::getline(itemFile, text);
	m_shield = stoi(text);

	std::getline(itemFile, text);
	m_speed = stof(text);

	std::getline(itemFile, text);
	m_att_speed = stof(text);

	std::getline(itemFile, text);
	m_damage = stof(text);

	itemFile.close();


}
