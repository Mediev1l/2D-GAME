#include "Item.h"
#include "AssetManager/AssetManager.h"
Texture* Item::_texture = nullptr;
Item::Item()
	: 
	  Stats() 
	 , onMap(true)
	{}

void Item::Create(std::string itemdatapath)
{
	std::fstream itemFile;
	std::string line;

	itemFile.open(itemdatapath);

	if (!itemFile.good())
		std::cerr << "Couldnt load the file";


	// Na razie na sztywno || do zmiany
	std::getline(itemFile, line);
	ID = stoi(line);

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

}

SpeedBoots::SpeedBoots()
{
	Create("res/Data/Items/SpeedBoots.txt");
}

BMW::BMW()
{
	Create("res/Data/Items/BMW.txt");
}

Yamaha::Yamaha()
{
	Create("res/Data/Items/Yamaha.txt");
}

Cpp::Cpp()
{
	Create("res/Data/Items/C++.txt");
}

Dzban::Dzban()
{
	Create("res/Data/Items/Dzban.txt");
}

Wfis::Wfis()
{
	Create("res/Data/Items/Wfis.txt");
}
