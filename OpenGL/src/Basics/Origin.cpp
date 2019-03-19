#include "Origin.h"



Origin::Origin()
{
}

Origin::Origin(unsigned int nVertex, Vec2d Size, Vec2d _position)
	:
	_size(Size)
	,_center(_position)
{
	//nVertexes poniewa¿ jak bedziemy chcieli robiæ wielok¹ty o innej ilosci bokow to sie kurwa przyda elo.
	//Kwadraty he,he
	double halfx = Size._x / 2;
	double halfy = Size._y / 2;
	_vertexs.emplace_back(_position._x - halfx, _position._y - halfy);
	_vertexs.emplace_back(_position._x + halfx, _position._y - halfy);
	_vertexs.emplace_back(_position._x + halfx, _position._y + halfy);
	_vertexs.emplace_back(_position._x - halfx, _position._y + halfy);
}								


Origin::~Origin()
{
}

void Origin::Update(bool ox, Vec2d & _position)
{
	if (ox)
	{
		_vertexs[0].setX(_position.getX() - _size._x / 2.0);
		_vertexs[1].setX(_position.getX() + _size._x / 2.0);
		_vertexs[2].setX(_position.getX() + _size._x / 2.0);
		_vertexs[3].setX(_position.getX() - _size._x / 2.0);
	}										
	else									
	{										
		_vertexs[0].setY(_position.getY() - _size._y / 2.0);
		_vertexs[1].setY(_position.getY() - _size._y / 2.0);
		_vertexs[2].setY(_position.getY() + _size._y / 2.0);
		_vertexs[3].setY(_position.getY() + _size._y / 2.0);
	}
	_center = _position;
}
