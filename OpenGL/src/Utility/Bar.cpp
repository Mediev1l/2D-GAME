#include "Bar.h"

Bar::Bar()
	:_texture(nullptr)
	,_width(5.0)
	,_height(0.5)
	,_currentvalue(0.0)
	,_maxvalue(1.0)
	,_visible(false)
{

}

Bar::~Bar()
{
}

double Bar::getX()
{
	return _x;
}

double Bar::getY()
{
	return _y;
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
	_x = x;
}

void Bar::setY(double y)
{
	_y = y;
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

void Bar::ShowBar()
{
	_visible = true;
}

void Bar::Hidebar()
{
	_visible = false;
}
