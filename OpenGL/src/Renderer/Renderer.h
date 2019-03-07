#ifndef RENDERER_H
#define RENDERER_H
#include "Maps/Map.h"
#include "Characters/Character.h"
#include "Items/Item.h"
#include "Renderer/Camera.h"
#include "glm.hpp"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
class Renderer
{
public:
	Renderer(const Camera& cam);
	~Renderer();

	void Render( std::vector<Character>&characters, std::vector<Item>&items);
	Map& getMap() { return _maps; };

	void CloseDoors() { DoorState = Object::DoorClosed; };
	void OpenDoors() { DoorState = Object::DoorOpened; };
private:

	void draw(double x, double y, GLuint IdTexture, double scale=0.0);
	void RenderMap();
	void RenderCharacters(std::vector<Character>& _characters);
	void RenderItems(std::vector<Item>& items);
	enum Object
	{
		DoorOpened = 0,
		DoorClosed = 1
	};

	void DrawDoors(Object& obj);
	//Drawing values
	double ScaleFactorX;
	double ScaleFactorY;
	double StartPosX;
	double StartPosY;
	double TranslateValueX;
	double TranslateValueY;

	//Main renderShader
	Shader _mainShader;
	

	//Current and next map
	Map _maps;

	//Reference to camera
	const Camera& cam;



	//Basic objects on EveryMap
	//Vektor na drzwi,tabliczki etc
	Object DoorState;
	std::vector<Texture> _objects;

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