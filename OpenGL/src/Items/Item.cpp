#include "Item.h"
#include "AssetManager/AssetManager.h"
Item::Item()
	: 
	  Stats() 
	 , onMap(true)
	{}

void Item::Create(std::string itemdatapath, Texture * text)
{
	std::fstream itemFile;
	std::string line;

	itemFile.open(itemdatapath);

	if (!itemFile.good())
		std::cerr << "Couldnt load the file";


	// Na razie na sztywno || do zmiany
	std::getline(itemFile, line);
	id = stoi(line);

	std::getline(itemFile, line);
	sName = line;

	std::getline(itemFile, line);
	description = line;

	std::getline(itemFile, line);
	m_health = stoi(line);

	std::getline(itemFile, line);
	m_shield = stoi(line);

	std::getline(itemFile, line);
	m_speed = stod(line);

	std::getline(itemFile, line);
	m_att_speed = stod(line);

	std::getline(itemFile, line);
	m_damage = stod(line);

	itemFile.close();

	_texture = text;

}

SpeedBoots::SpeedBoots()
{
	Create("res/Items/SpeedBoots.txt", AssetManager::Get().getSprite("SpeedBoots"));
}
