#include "Bar.h"

Bar::Bar()
	:_texture(nullptr)
	,_renderer(nullptr)
	,_width(5.0)
	,_height(0.5)
	,_currentvalue(0.0)
	,_maxvalue(1.0)
	,_visible(false)
	//Coords(0,0)
{
	
}

Bar::~Bar()
{
}

double Bar::getX()
{
	return Coords::_position._x;
}

double Bar::getY()
{
	return Coords::_position._y;
}

double Bar::getWidth()
{
	return _width;
}

double Bar::getHeight()
{
	return _height;
}

double Bar::getCurrent()
{
	return _currentvalue;
}

double Bar::getMax()
{
	return _maxvalue;
}

bool Bar::getVisible()
{
	return _visible;
}

Texture * Bar::getTexture()
{
	return _texture;
}

void Bar::setX(double x)
{
	Coords::_position._x = x;
}

void Bar::setY(double y)
{
	Coords::_position._y = y;
}

void Bar::setCoords(double x, double y)
{
	Coords::_position._x = x;
	Coords::_position._y = y;
}

void Bar::setWidth(double width)
{
	_width = width;
}

void Bar::setHeight(double height)
{
	_height = height;
}

void Bar::setCurrent(double current)
{
	_currentvalue = current;
}

void Bar::setMax(double max)
{
	_maxvalue = max;
}

void Bar::Init(Renderer * renderer)
{
	_renderer = renderer;
	_texture = AssetManager::Get().getSprite("hp");
}

void Bar::ShowBar()
{
	_visible = true;
}

void Bar::Hidebar()
{
	_visible = false;
}

void Bar::DrawSelf()
{
	double moveX = 0;
	if (_currentvalue < _maxvalue)
		moveX = _currentvalue / _maxvalue * 1.5 - 1.5;
	
	
	_renderer->drawSelf(Coords::_position._x  + moveX , Coords::_position._y, _texture->getID(), _currentvalue / _maxvalue  * 0.5 , _height * 0.1, glm::vec4(1.0, 0.0, 0.0, 1.0));
}
