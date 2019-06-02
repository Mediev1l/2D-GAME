

#ifndef _Bar_H
#define _Bar_H

#include "Basics/Coords.h"
#include "Renderer/Texture.h"
#include "Renderer/Renderer.h"
#include "AssetManager/AssetManager.h"

class Bar : public Coords
{
private:

	double _width;
	double _height;
	double _currentvalue;
	double _maxvalue;

	Texture* _texture;
	Renderer* _renderer;

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
	void setCoords(double x, double y);
	void setWidth(double width);
	void setHeight(double height);
	void setCurrent(double current);
	void setMax(double max);

	//================================================================
	//= Methods
	//================================================================

	void Init(Renderer* renderer);
	void ShowBar();
	void Hidebar();
	void DrawSelf();


};

#endif

