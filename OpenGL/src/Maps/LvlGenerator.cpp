#include "LvlGenerator.h"

LvlGenerator::LvlGenerator(std::string BlockListPath)
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

std::vector<std::pair<int,bool>> LvlGenerator::generateLevel(GLuint width, GLuint height)
{
	srand((GLuint)time(NULL));

	GLuint x = (GLuint)ceil(width / 2.0) - 1;
	GLuint y = (GLuint)ceil(height / 2.0) - 1;
	GLuint id[] = { x,0,0,y,width - 1,y };

	auto Doors = [&](GLuint x, GLuint y) -> bool
	{
		for (GLuint i = 0; i < 6; i += 2)
		{
			if (x == id[i] || y == id[i + 1]) return true;
		}
		return false;
	};

	std::vector<std::pair<int, bool>> genlevel;
	genlevel.reserve((width - 2)*(height - 2));

	for(GLuint y=1;y<height-1;++y)
		for (GLuint x = 1; x < width-1; ++x)
		{
			GLuint xd = rand() % _leveldata.size();
			if (!Doors(x, y)) genlevel.emplace_back(_leveldata[xd].first, _leveldata[xd].second);
			else genlevel.emplace_back(9,false);
		}
	return genlevel;
}
