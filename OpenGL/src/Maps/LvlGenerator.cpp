#include "LvlGenerator.h"

LvlGenerator::LvlGenerator(std::string BlockListPath):device(),eng(device())
{
	std::fstream plik;
	plik.open(BlockListPath, std::ios::in);

	if (!plik.good())
	{
		throw std::runtime_error("Nie udalo siê wczytaæ danych do generatora | Path: " + BlockListPath);
	}
	size_t ile;
	plik >> ile;
	_leveldata.reserve(ile);
	for (size_t i=0; i < ile; ++i)
	{
		int a, b;
		plik >> a >> b;
		_leveldata.emplace_back(a, b == 0 ? false : true);
	}

	plik.close();
}

LvlGenerator::~LvlGenerator()
{
}

std::vector<std::pair<int,bool>> LvlGenerator::generateLevel(Map* map,Difficulty diff)
{
	switch (diff)
	{
		case BEGIN:
		case EASY:
		{
			std::uniform_int_distribution<GLuint> xDist(6, 10);
			std::uniform_int_distribution<GLuint> yDist(6, 10);
			width = xDist(eng);
			height = yDist(eng);
			break;
		}
		case MEDIUM:
		{
			std::uniform_int_distribution<GLuint> xDist(10, 25);
			std::uniform_int_distribution<GLuint> yDist(10, 25);
			width = xDist(eng);
			height = yDist(eng);
			break;
		}
		case HARD:
		{
			std::uniform_int_distribution<GLuint> xDist(25, 40);
			std::uniform_int_distribution<GLuint> yDist(25, 40);
			width = xDist(eng);
			height = yDist(eng);
			break;
		}
		default:
		{
			width = 5;
			height = 5;
		}
	}

	map->setWidth(width);
	map->setHeight(height);
	srand((GLuint)time(NULL));

	GLuint x = (GLuint)ceil(width / 2.0) - 1;
	GLuint y = (GLuint)ceil(height / 2.0) - 1;
	
	doorpos[0] = { x };
	doorpos[1] = { 0 };
	doorpos[2] = { 0 };
	doorpos[3] = { y };
	doorpos[4] = { width - 1 };
	doorpos[5] = { y };

	
	std::vector<std::pair<int, bool>> genlevel(width*height,std::make_pair(0,false));
	//genlevel.reserve((width)*(height));

	//Border
		//top
	for (int w = 0, ew = width; w < ew; ++w) genlevel[w] = { 1,true };
		//Bottom
	for (int w = 0, ew = width; w < ew; ++w) genlevel[(height-1)*width+w] = { 1,true };
		//Left
	for (int h = 0, ew = height; h < ew; ++h) genlevel[h*width] = { 1,true };
		//Right
	for (int h = 0, ew = height; h < ew; ++h) genlevel[h*width+(width-1)] = { 1,true };
		

	//Srodek mapy
	for(GLuint yp=1;yp<height-1;++yp)
		for (GLuint xp = 1; xp < width-1; ++xp)
		{
			GLuint xd = rand() % _leveldata.size();
			if (!Doors(xp, yp)) genlevel[yp*width + xp] = { _leveldata[xd].first, _leveldata[xd].second };
			else genlevel[yp*width+xp] = { 9,false };
		}
	return genlevel;
}

void LvlGenerator::PopulateDynamics(std::vector<Character>& ch, Difficulty diff)
{
	std::uniform_int_distribution<GLuint> xDist(1, width-2);
	std::uniform_int_distribution<GLuint> yDist(1, height-2);

	switch (diff)
	{
		case EASY:
		{	
			ch.push_back( Enemy("boss", doorpos[0], yDist(eng), 1.0, { 0.5,0.9 }, 9) );
			break;
		}
		case MEDIUM:
		{
			ch.push_back(Enemy("boss", doorpos[0], yDist(eng), 1.0, { 0.5,0.9 }, 9));
			ch.push_back(Enemy("skelly2", xDist(eng), doorpos[3], 1.0, { 0.5,0.9 }, 9));
			break;
		}
		case HARD:
		{
			ch.push_back(Enemy("boss", doorpos[0], yDist(eng), 1.0, { 0.5,0.9 }, 9));
			ch.push_back(Enemy("skelly2", xDist(eng), doorpos[3], 1.0, { 0.5,0.9 }, 9));
			ch.push_back(Enemy("bae", doorpos[0], yDist(eng), 1.0, { 0.5,0.9 }, 9));
			break;
		}
		
		case BEGIN:
		{
			ch.push_back(Enemy("skelly2", doorpos[0], yDist(eng), 1.0, { 0.5,0.9 }, 9));
			ch[1].setDamage(0);
			break;
		}
		default:
		{
			return;
		}
	}
}
