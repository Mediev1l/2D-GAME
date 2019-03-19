#include "Camera.h"



Camera::Camera()
{
}


Camera::Camera(GLuint width, GLuint height)
{
	Fov._x = width;
	Fov._y = height;
	_translateVector._x = 0.0;
	_translateVector._y = 0.0;
}

Camera::~Camera()
{
}

void Camera::initCamera(const Vec2d& pos, GLuint wscreen, GLuint hscreen)
{
	_w = wscreen;
	_h = hscreen;
	_scaleFactor = 1.0 / Fov._x;
	double tmpx = -2 * _scaleFactor * (pos._x - Fov._x / 2.0);
	double tmpy = 2 * _scaleFactor * (pos._y - Fov._y / 2.0);

	if (tmpx < 0)_translateVector._x = tmpx;
	else _translateVector._x = 0;

	if (tmpy > 0) _translateVector._y = tmpy;
	else _translateVector._y = 0;
}

void Camera::UpdateCamera(const Vec2d & pos, Vec2d center)
{
	double tmpx = -2 * _scaleFactor * (pos._x+center._x - Fov._x / 2.0);
	double tmpy = 2 * _scaleFactor * (pos._y+center._y - Fov._y / 2.0);
	
	bool right = pos._x+center._x < (double)_w - (Fov._x / 2.0);
	bool bottom = pos._y+center._y < (double)_h - (Fov._y / 2.0);

	if (tmpx < 0 && right)_translateVector._x = tmpx;
	else if (!right) _translateVector._x = -2 * _scaleFactor * (((double)_w - (Fov._x / 2.0)) - Fov._x / 2.0);
	else _translateVector._x = 0;

	if (tmpy > 0 && bottom) _translateVector._y = tmpy;
	else if (!bottom) _translateVector._y = 2 * _scaleFactor * ((double)_h - (Fov._y / 2.0) - Fov._y / 2.0);
	else _translateVector._y = 0;
}

