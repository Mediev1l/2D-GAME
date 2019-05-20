

#ifndef _Bar_H
#define _Bar_H

#include "Renderer/Texture.h"
#include "AssetManager/AssetManager.h"

class Bar
{
private:
	double _x;
	double _y;
	double _width;
	double _height;
	double _currentvalue;
	double _maxvalue;

	Texture* _texture;

	bool _visible;
	
public:
	Bar();
	~Bar();

	//================================================================
	//= Gettery
	//================================================================

	double getX();
	double getY();
	double getWidth();
	double getHeight();
	double getCurrent();
	double getMax();
	bool getVisible();
	Texture* getTexture();

	//================================================================
	//= Gettery
	//================================================================

	void setX(double x);
	void setY(double y);
	void setWidth(double width);
	void setHeight(double height);
	void setCurrent(double current);
	void setMax(double max);

	//================================================================
	//= Methods
	//================================================================

	void ShowBar();
	void Hidebar();


};

#endif

