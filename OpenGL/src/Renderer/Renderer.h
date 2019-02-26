#ifndef RENDERER_H
#define RENDERER_H
#include "Maps/Map.h"
class Renderer
{
public:
	Renderer();
	~Renderer();

	void Render();
private:
	//Current and next map
	Map _maps[2];

	//Main renderShader
	Shader _mainShader;

	//Vbo vao ebo itp
	unsigned int VBO, VAO, EBO;

	float vertices[20] = {
		// positions          // textures coords
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,   1.0f, 1.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 1.0f,  // bottom left
		-0.5f,  0.5f, 0.0f,   0.0f, 0.0f,  // top left 
	};

	//================================================================
	//= Facey
	//================================================================
	unsigned int indices[6] = {  // note that we start from 0!
	0, 1, 3,  // first Triangle
	1, 2, 3   // second Triangle
	};
};
#endif