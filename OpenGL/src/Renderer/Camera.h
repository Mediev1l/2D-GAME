#ifndef CAMERA_H
#define CAMERA_H
#include "Utility/Vec2.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Characters/Character.h"
class Camera
{
public:
	Camera();
	Camera(GLuint width, GLuint height);
	~Camera();

	const Vec2i& getFov()const { return Fov; };
	const Vec2d& getTranslate()const { return _translateVector; };
	void initCamera(const Vec2d& pos, GLuint wscreen, GLuint hscreen);
	void UpdateCamera(const Vec2d & pos, Vec2d center);
private:
	Vec2d _translateVector;
	Vec2i Fov;
	double _scaleFactor;
	GLuint _w;
	GLuint _h;
};
#endif
