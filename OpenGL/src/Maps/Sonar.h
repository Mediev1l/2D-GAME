#ifndef SONAR_H
#define SONAR_H
#include <vector>
#include "Maps/Map.h"
//Dijkstra xD
class Dijkstra
{
public:
	struct Edge
	{
		Edge(GLuint p, long long pr) : ID(p), tripPrice(pr) {};
		GLuint ID;
		long long tripPrice;
	};
	struct Vertex
	{
		Vertex() : ID(0), tripPrice(-1), poprzednik(nullptr), krawedz() {};
		Vertex(GLuint ID, long long tp, Vertex* p) : ID(ID), tripPrice(tp), poprzednik(p) {};
		GLuint ID;
		long long tripPrice;
		Vertex* poprzednik;
		std::vector<Edge> krawedz;
	};
public:
	Dijkstra() = delete;
	static Vertex* CalculateFor(GLuint start, GLuint end)
	{
		//Je¿eli nic nie ma w Q
		if (Q.size() == 0)
		{
			Q.clear();
			if (S.size() == 0) return nullptr;
			Q.reserve(S.size());
			//To skopiuj z S
			for (GLuint i = 0; i < S.size(); ++i)
			{
				Q.push_back(S[i]);
			}
		}

		//Wyczyœæ wszystko
		S.clear();
		S.reserve(Q.size());
		for (GLuint i = 0; i < Q.size(); ++i)
		{
			Q[i].poprzednik = nullptr;
			if (Q[i].ID != start)Q[i].tripPrice = MAX_INT;
			else Q[i].tripPrice = 0;
		}

		while (Q.size() > 0)
		{
			//Znajdz wierzcho³ek o najmniejszej drodze dojscia
			GLuint minID = 0;
			long long min = Q[0].tripPrice;
			for (GLuint i = 1; i < Q.size(); ++i)
			{
				if (Q[i].tripPrice < (long long)min)
				{
					min = Q[i].tripPrice;
					minID = i;
				}
			}

			//Wyrzuc z Q dodaj do S
			S.push_back(Q[minID]);
			Q[minID] = Q[Q.size() - 1];
			Q.pop_back();

			Vertex* current = &S[S.size() - 1];
			//Dla ka¿dego s¹siada 
			for (GLuint i = 0; i < current->krawedz.size(); ++i)
			{
				//Który jest w zbiorze Q
				Vertex* szukany = exist(current->krawedz[i].ID, Q);
				if (szukany != nullptr)
				{
					if (szukany->tripPrice > current->tripPrice + current->krawedz[i].tripPrice)
					{
						szukany->tripPrice = current->tripPrice + current->krawedz[i].tripPrice;
						szukany->poprzednik = current;
					}
				}
			}
		}

		for (GLuint i = 0, e = S.size(); i < e; ++i)
		{
			if (S[i].ID == end) return &S[i];
		}
		return nullptr;
	}
	static void loadVertex(GLuint ID)
	{
		Q.emplace_back(ID, MAX_INT, nullptr);
	};
	static void loadEdge(GLuint ID, GLuint IDDest, long long cost)
	{
		for (GLuint i = 0, e = Q.size(); i < e; ++i)
		{
			if (Q[i].ID == ID)
			{
				Q[i].krawedz.emplace_back(IDDest, cost);
				break;
			}
		}
	};
	static void ClearAll() { Q.clear(); S.clear(); nVertex = 0; nEdges = 0; };
	static std::vector<Vertex> getSolution() { return S; };
private:
	static Vertex* exist(GLuint ID, std::vector<Vertex>&Q)
	{
		for (GLuint i = 0; i < Q.size(); ++i)
		{
			if (ID == Q[i].ID) return &Q[i];
		}
		return nullptr;
	}
private:
	static std::vector<Vertex> Q;
	static std::vector<Vertex> S;
public:
	static const long long MAX_INT;
	static GLuint nVertex;
	static GLuint nEdges;
};
std::vector<Dijkstra::Vertex> Dijkstra::Q;
std::vector<Dijkstra::Vertex> Dijkstra::S;
GLuint Dijkstra::nVertex = 0;
GLuint Dijkstra::nEdges = 0;
const long long Dijkstra::MAX_INT = 4000000000000000000;


class Sonar
{
public:
	Sonar();
	~Sonar();

	void createGraph(Map* map);
	std::vector<GLuint> getPathFor(GLuint start, GLuint end);
private:
};

#endif