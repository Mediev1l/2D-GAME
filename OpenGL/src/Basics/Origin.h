#ifndef ORIGIN_H
#define ORIGIN_H
//#include "GL/glew.h"
#include <vector>
#include "Utility/Vec2.h"
class Origin
{
public:
	Origin();
	Origin(unsigned int nVertex, Vec2d Size, Vec2d _position);
	~Origin();

	//Gettery
	unsigned int getVertexCount() const
	{
		return (unsigned int)_vertexs.size();
	};
	Vec2d& getVertex(unsigned int x)
	{
		return _vertexs[x];
	};
	Vec2d& getCenter() { return _center; };
	Vec2d& getSize() { return _size; };
	//Utils
	void Update(bool ox, Vec2d& _position);
private:
	std::vector<Vec2d> _vertexs;
	Vec2d _center;
	Vec2d _size;
};
#endif