#include "Item.h"

Item::Item(const std::string& TexturePath,const std::string& ItemPath, GLuint itemID)
	: 
	   id(itemID)
	 , Stats() 
	 , onMap(true)
	 , _texture(TexturePath + "item_" + std::to_string(itemID) + ".png",true)
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
	m_speed = stod(text);

	std::getline(itemFile, text);
	m_att_speed = stod(text);

	std::getline(itemFile, text);
	m_damage = stod(text);

	itemFile.close();
}
