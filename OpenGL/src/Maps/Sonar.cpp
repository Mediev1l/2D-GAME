/*#include "Sonar.h"

std::vector<Dijkstra::Vertex> Dijkstra::Q;
std::vector<Dijkstra::Vertex> Dijkstra::S;
GLuint Dijkstra::nVertex = 0;
GLuint Dijkstra::nEdges = 0;
const long long Dijkstra::MAX_INT = 4000000000000000000;


Sonar::Sonar()
{
}


Sonar::~Sonar()
{
}

void Sonar::createGraph(Map * map)
{
	Dijkstra::ClearAll();

	GLuint width = map->getWidth();
	GLuint height = map->getHeight();

	auto getIndex = [&](GLuint x, GLuint y) { return y * width + x; };

	for(int y=0;y<height;++y)
		for (int x = 0; x < width; ++x)
		{
			if (map->getTile(getIndex(x, y)).GetSolid() == false)
			{
				Dijkstra::loadVertex(getIndex(x, y));
				if (x - 1 > 0) if (!map->getTile(getIndex(x - 1, y)).GetSolid())Dijkstra::loadEdge(getIndex(x, y), getIndex(x - 1, y), 1);
				if (x + 1 < width) if (!map->getTile(getIndex(x + 1, y)).GetSolid())Dijkstra::loadEdge(getIndex(x, y), getIndex(x + 1, y), 1);
				if (y - 1 > 0)if (!map->getTile(getIndex(x, y - 1)).GetSolid())Dijkstra::loadEdge(getIndex(x, y), getIndex(x, y - 1), 1);
				if (y + 1 < height) if (!map->getTile(getIndex(x, y + 1)).GetSolid())Dijkstra::loadEdge(getIndex(x, y), getIndex(x, y + 1), 1);
			}
		}
}

std::vector<GLuint> Sonar::getPathFor(GLuint start, GLuint end)
{
	std::vector<GLuint> path;
	Dijkstra::Vertex* tmp = Dijkstra::CalculateFor(start, end);
	while (tmp->ID != start)
	{
		path.push_back(tmp->ID);
		tmp = tmp->poprzednik;
		if (tmp == nullptr) break;
	}
	//std::cout << path[0] << " ";
	std::reverse(path.begin(), path.end());

	return path;
}
*/