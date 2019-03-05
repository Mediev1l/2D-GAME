#ifndef CAMERA_H
#define CAMERA_H
#include "Utility/Vec2.h"
class Camera
{
public:
	Camera();
	~Camera();
private:
	Vec2d Fov;
};
#endif
