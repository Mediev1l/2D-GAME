#ifndef RENDERER_H
#define RENDERER_H
#include "Maps/Map.h"
#include "Characters/Character.h"
#include "Items/Item.h"
#include "Renderer/TextGenerator.h"
#include "Renderer/Camera.h"
#include "glm.hpp"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "AssetManager/AssetManager.h"


class Renderer
{
public:
	Renderer(const Camera& cam);
	~Renderer() { delete _maps; };

	void Render( std::vector<Character>&characters, std::vector<Item*>*items, const TextGenerator& text);
	Map* getMap() { return _maps; };

	void CloseDoors() { DoorState = Object::DoorClosed; };
	void OpenDoors() { DoorState = Object::DoorOpened; };

	void ScreenDimm(float perc = 1.0f);
	void ScreenBright();

	bool isDark() { return GammaRatio.x <= 1.0f - percentage; };
	bool isBright() { return GammaRatio.x >= 1.0; };
	void setDelta(double delta);
private:

	void setTextureCoords(Tile& tile);
	void setTextureCoords(Character& obj);
	void setTextureCoords(Projectile& proj);
	void setTextureCoords(GLuint x);
	void setTextureCoords(Vec2i pos);
	void draw(double x, double y, GLuint IdTexture, double scale=0.0 );
	void drawText(double x, double y, GLuint IdTexture, Vec2d scale, glm::vec4 color);
	void RenderMap();
	void RenderCharacters(std::vector<Character>& _characters);
	void RenderItems(std::vector<Item*>* items);
	void RenderText(const TextGenerator& text);
	

	//Doors Stuff
	enum Object
	{
		DoorOpened = 1,
		DoorClosed = 0
	};
	Texture* doors;
	void DrawDoors(Object& obj);


	//Drawing values
	double ScaleFactorX;
	double ScaleFactorY;
	double StartPosX;
	double StartPosY;
	double TranslateValueX;
	double TranslateValueY;
	glm::vec4 GammaRatio;
	float percentage;
	float dimmRatio;
	double Delta;
	

	//Main renderShader
	Shader _SpriteSheetShader;

	//Current and next map
	Map* _maps;

	//Reference to camera
	const Camera& cam;



	//Basic objects on EveryMap
	//Vektor na drzwi,tabliczki etc
	Object DoorState;

	//Vbo vao ebo itp
	unsigned int VBO[2], VAO[2], EBO[2];

	//Dla mapy
	float vertices[20] = {
		// positions          // textures coords
		1.0f,  1.0f, 0.0f,   0.1f, 1.0f,  // top right
		1.0f, -1.0f, 0.0f,   0.1f, 0.75f,  // bottom right
		-1.0f, -1.0f, 0.0f,   0.0f, 0.75f,  // bottom left
		-1.0f,  1.0f, 0.0f,   0.0f, 1.0f,  // top left 
	};

	//================================================================
	//= Facey
	//================================================================
	unsigned int indices[6] = {  // note that we start from 0!
	0, 1, 3,  // first Triangle
	1, 2, 3   // second Triangle
	};


	////Tymczasowo dla reszty ferajny
	//float vertices2[20] = {
	//	// positions          // textures coords
	//	1.0f,  1.0f, 0.0f,   1.0f, 1.0f,  // top right
	//	1.0f, -1.0f, 0.0f,   1.0f, 0.0f,  // bottom right
	//	-1.0f, -1.0f, 0.0f,   0.0f, 0.0f,  // bottom left
	//	-1.0f,  1.0f, 0.0f,   0.0f, 1.0f,  // top left 
	//};




	//float vertices[20] = {
	//	// positions          // textures coords
	//	0.5f,  0.5f, 0.0f,  
	//	0.5f, -0.5f, 0.0f,  
	//	-0.5f, -0.5f, 0.0f, 
	//	-0.5f,  0.5f, 0.0f,  
	//};

	
};
#endif