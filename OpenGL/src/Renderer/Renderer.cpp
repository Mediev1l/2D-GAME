#include "Renderer.h"



Renderer::Renderer(const Camera& camera)
	:
	_mainShader("src/Shaders/vs.vs","src/Shaders/fs2.fs")
	,_SpriteSheetShader("src/Shaders/vs.vs", "src/Shaders/fs.fs")
	, _objects{ {"res/Sprites/Objects/opened.png",true} ,{"res/Sprites/Objects/closed.png",true} }
	,cam(camera)
{
	//Ustawienie gammy na full
	GammaRatio = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	glGenVertexArrays(2, VAO);
	glGenBuffers(2, VBO);
	glGenBuffers(2, EBO);
	glBindVertexArray(VAO[0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);

	glBindVertexArray(VAO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);


	//To ma byæ wywo³ane przed u¿yciem jakiejkolwiek tekstury
	_mainShader.use();
	_mainShader.setInt("texture1", 0);
	_SpriteSheetShader.use();
	_SpriteSheetShader.setInt("texture1", 0);
	//Setup Drawin Values
	//ScaleFactorX = 1.0 / _maps.getWidth();
	//ScaleFactorY = 1.0 / _maps.getHeight();

	ScaleFactorX = 1.0 / cam.getFov()._x;
	ScaleFactorY = 1.0 / cam.getFov()._y;

	StartPosX = 1 -ScaleFactorX;
	StartPosY = 1 -ScaleFactorY;

	TranslateValueX = 2 * ScaleFactorX;
	TranslateValueY = 2 * ScaleFactorY;

	DoorState = Object::DoorClosed;
	AssetManager::Get();
	AssetManager::Get().LoadSprites();
	AssetManager::Get().LoadMaps();
	AssetManager::Get().LoadItems();
	_maps = AssetManager::Get().getMap("Basement");
}


void Renderer::Render( std::vector<Character>&characters, std::vector<Item*>*items)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_SpriteSheetShader.use();
	_SpriteSheetShader.setVec4("Gamma", GammaRatio);
	_mainShader.use();
	_mainShader.setVec4("Gamma", GammaRatio);
	RenderMap();
	RenderItems(items);
	RenderCharacters(characters);
}



void Renderer::RenderMap()
{
	for (GLuint y = 0; y < (GLuint)_maps->getHeight(); y++)
	{
		for (GLuint x = 0; x < (GLuint)_maps->getWidth(); x++)
		{
			setTextureCoords(_maps->getTile(x,y));
			draw(_maps->getTilePos(x, y)._x, _maps->getTilePos(x, y)._y, _maps->getTexture()->getID(),true);
		}
	}
	DrawDoors(DoorState);
}

void Renderer::RenderCharacters( std::vector<Character>& characters)
{
	//Rysowanie od ty³u = gracz zawsze na wierzchu
	for(int i = (int)characters.size()-1; i>-1;--i)
	{
		if (i == 0)
		{
			for (int i = (int)characters[0].getPifPafSize() - 1; i > -1; --i)
			{
				if (characters[0].getOnepiFpaF(i).getExistance() == true)
				{
					draw(characters[0].getOnepiFpaF(i)._position.getX(), characters[0].getOnepiFpaF(i)._position.getY(), characters[0].getPifPafTexture(),false,0.05);
				}
			}
			setTextureCoords(characters[i]);
			draw(characters[i].getPos()._x, characters[i].getPos()._y, characters[i].getTexture(),true);
			break;
		}
		setTextureCoords(characters[i]);
		draw(characters[i].getPos()._x, characters[i].getPos()._y, characters[i].getTexture(),true);
	}
}

void Renderer::RenderItems( std::vector<Item*>* items)
{
	_SpriteSheetShader.use();

	//Od ty³u bo sobie skopiowa³em z characters kappa
	for (int i = (int)items->size()-1; i > -1; --i)
	{
		if ((*items)[i]->getOnMap() == true)
		{
			draw((*items)[i]->getX(), (*items)[i]->getY(), (*items)[i]->getTexture(),false);
		}
	}
}

void Renderer::ScreenDimm()
{
	
	if (GammaRatio.x > 0) GammaRatio.x -= 0.008f;
	if (GammaRatio.y > 0) GammaRatio.y -= 0.008f;
	if (GammaRatio.z > 0) GammaRatio.z -= 0.008f;

}

void Renderer::ScreenBright()
{
	if (GammaRatio.x < 1) GammaRatio.x += 0.008f;
	if (GammaRatio.y < 1) GammaRatio.y += 0.008f;
	if (GammaRatio.z < 1) GammaRatio.z += 0.008f;
}

void Renderer::setTextureCoords(Tile & tile)
{
	GLuint nr = tile.getTextureNumber();
	float offsetx = (float)nr*0.1f;
	_SpriteSheetShader.setFloat("offsetX", offsetx);
	_SpriteSheetShader.setFloat("offsetY", 0);
}

void Renderer::setTextureCoords(Character & obj)
{
	Vec2i pos = obj.getFrameIndex();
	float offsetx = (float)pos._x*0.1f;
	float offsety = (float)pos._y*0.25f;
	_SpriteSheetShader.setFloat("offsetX", offsetx);
	_SpriteSheetShader.setFloat("offsetY", offsety);

	//std::cout << "OffsetX: " << offsetx << '\n';
	//std::cout << "OffsetY: " << offsety << '\n';
}

void Renderer::draw(double x, double y,GLuint IdTexture, bool map, double scale)
{

	//Eksperymentalnie udowodniono ze dziala xD
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-StartPosX, StartPosY, 0.0f));
	model = glm::translate(model, glm::vec3(TranslateValueX*x, -TranslateValueY * y, 0.0f));
	model = glm::translate(model, glm::vec3((float)cam.getTranslate()._x, (float)cam.getTranslate()._y, 0.0f));


	//Skalowanko lepiej na koncu xD
	model = glm::scale(model, glm::vec3(scale > 0 ? scale:ScaleFactorX, scale > 0 ? scale : ScaleFactorY, 0.0f));


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, IdTexture);

	if (map==false)
	{
		_mainShader.use();
		_mainShader.setMat4("model", model);
		glBindVertexArray(VAO[1]);
	}
	else
	{
		_SpriteSheetShader.use();
		_SpriteSheetShader.setMat4("model", model);
		glBindVertexArray(VAO[0]);
	}
	

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}

void Renderer::DrawDoors(Object & obj)
{
	GLuint x = (GLuint)ceil(_maps->getWidth() / 2.0) - 1;
	GLuint y = (GLuint)ceil(_maps->getHeight() / 2.0) - 1;
	GLuint id[] = { x,0,0,y,_maps->getWidth() - 1,y };
	//RenderDoors
	for (GLuint i = 0; i < 6; i += 2)
	{

		//Eksperymentalnie udowodniono ze dziala xD
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-StartPosX, StartPosY, 0.0f));
		model = glm::translate(model, glm::vec3(TranslateValueX*id[i], -TranslateValueY * id[i + 1], 0.0f));
		model = glm::translate(model, glm::vec3((float)cam.getTranslate()._x, (float)cam.getTranslate()._y, 0.0f));
		//Obracanie drzwi he he
		if (i == 2)
		{
			model = glm::rotate(model, (float)glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		}
		if (i == 4)
		{
			model = glm::rotate(model, (float)glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		}
		

		//Skalowanko lepiej na koncu xD
		model = glm::scale(model, glm::vec3(ScaleFactorX, ScaleFactorY, 0.0f));


		

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _objects[obj].getID());

		_mainShader.use();
		_mainShader.setMat4("model", model);
		glBindVertexArray(VAO[1]);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}
