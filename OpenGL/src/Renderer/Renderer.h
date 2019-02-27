#ifndef RENDERER_H
#define RENDERER_H
#include "Maps/Map.h"
#include "glm.hpp"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
class Renderer
{
public:
	Renderer();
	~Renderer();

	void Render();
private:

	//Main renderShader
	Shader _mainShader;


	//Current and next map
	Map _maps;

	

	//Vbo vao ebo itp
	unsigned int VBO, VAO, EBO;

	float vertices[20] = {
		// positions          // textures coords
		1.0f,  1.0f, 0.0f,   1.0f, 1.0f,  // top right
		1.0f, -1.0f, 0.0f,   1.0f, 0.0f,  // bottom right
		-1.0f, -1.0f, 0.0f,   0.0f, 0.0f,  // bottom left
		-1.0f,  1.0f, 0.0f,   0.0f, 1.0f,  // top left 
	};

	//float vertices[20] = {
	//	// positions          // textures coords
	//	0.5f,  0.5f, 0.0f,  
	//	0.5f, -0.5f, 0.0f,  
	//	-0.5f, -0.5f, 0.0f, 
	//	-0.5f,  0.5f, 0.0f,  
	//};

	//================================================================
	//= Facey
	//================================================================
	unsigned int indices[6] = {  // note that we start from 0!
	0, 1, 3,  // first Triangle
	1, 2, 3   // second Triangle
	};
};
#endif