#include "Renderer.h"



Renderer::Renderer(const Camera& camera)
	:
	_SpriteSheetShader("src/Shaders/vs.vs", "src/Shaders/fs.fs")
	, cam(camera)
	, percentage(1.0f)
	, dimmRatio(0.0f)
{
	//Ustawienie gammy na full
	GammaRatio = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	glGenVertexArrays(1, VAO);
	glGenBuffers(1, VBO);
	glGenBuffers(1, EBO);
	glBindVertexArray(*VAO);

	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);

	//To ma by� wywo�ane przed u�yciem jakiejkolwiek tekstury
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
	doors = AssetManager::Get().getSprite("obj");
}


void Renderer::Render( std::vector<Character>&characters, std::vector<Item*>*items, const TextGenerator& text)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	_SpriteSheetShader.use();
	RenderMap();
	RenderItems(items);
	RenderCharacters(characters);
	RenderText(text);
	_SpriteSheetShader.setVec4("Gamma", GammaRatio);
}



void Renderer::RenderMap()
{
	srand(0);
	GLuint x = (GLuint)ceil(_maps->getWidth() / 2.0) - 1;
	GLuint y = (GLuint)ceil(_maps->getHeight() / 2.0) - 1;
	GLuint id[] = { x,0,0,y,_maps->getWidth() - 1,y };

	for (GLuint y = 0; y < (GLuint)_maps->getHeight(); y++)
	{
		for (GLuint x = 0; x < (GLuint)_maps->getWidth(); x++)
		{
			if ( (x != id[0] || y != id[1]) && (x != id[2] || y != id[3]) && (x != id[4]  || y != id[5]) )
			{
				setTextureCoords(_maps->getTile(x, y));
				draw(_maps->getTilePos(x, y)._x, _maps->getTilePos(x, y)._y, _maps->getTexture()->getID());
			}
		}
	}
	DrawDoors(DoorState);
}

void Renderer::RenderCharacters( std::vector<Character>& characters)
{
	//Rysowanie od ty�u = gracz zawsze na wierzchu
	for(int i = (int)characters.size()-1; i>-1;--i)
	{
		if (i == 0)
		{
			for (int i = (int)characters[0].getPifPafSize() - 1; i > -1; --i)
			{
				if (characters[0].getOnepiFpaF(i).getExistance() == true)
				{
					setTextureCoords(characters[0].getOnepiFpaF(i));
					draw(characters[0].getOnepiFpaF(i)._position.getX(), characters[0].getOnepiFpaF(i)._position.getY(), characters[0].getPifPafTexture(),0.05);
				}
			}
			setTextureCoords(characters[i]);
			draw(characters[i].getPos()._x, characters[i].getPos()._y, characters[i].getTexture());
			break;
		}
		setTextureCoords(characters[i]);
		draw(characters[i].getPos()._x, characters[i].getPos()._y, characters[i].getTexture());
	}
}

void Renderer::RenderItems( std::vector<Item*>* items)
{
	_SpriteSheetShader.use();

	//Od ty�u bo sobie skopiowa�em z characters kappa
	for (int i = (int)items->size()-1; i > -1; --i)
	{
		if ((*items)[i]->getOnMap() == true)
		{

			setTextureCoords((*items)[i]->getID());
			draw((*items)[i]->getX(), (*items)[i]->getY(), (*items)[i]->getTexture());
		}
	}
}

void Renderer::RenderText(const TextGenerator& text)
{

	for (size_t i = 0; i < text.getAmount(); i++)
	{	
		if (text.CheckDrawing(i) == true)
		{
			double counter = 0;
			for (auto x : text.getText(i))
			{
				Vec2ic sheetPos = text.getSheetPosition(toupper(x));
				Vec2dc textPos = text.getPosition(i);

				glm::vec4 tempColor = text.getColor(i);
				if (dimmRatio > 0)
				{
					tempColor.r -= dimmRatio;
					tempColor.g -= dimmRatio;
					tempColor.b -= dimmRatio;
				}
				
				if (tempColor.a <= 1.0f && text.getFinish(i) == false) text.setTransparency(i, tempColor.a += 0.2f * Delta);
				else if (tempColor.a >= 0.0f && text.getFinish(i) == true) text.setTransparency(i, tempColor.a -= 0.2f * Delta);

				setTextureCoords(sheetPos);
				drawText(textPos._x + counter*text.getSize(i)._x*5, textPos._y, text.getTexture(), text.getSize(i), tempColor);
				counter++;
			}
	
		}
	}

}

void Renderer::ScreenDimm(float perc)
{
	percentage = perc;
	if (GammaRatio.x > 1.0f - percentage) dimmRatio += Delta;//0.008f;
	if (GammaRatio.x > 1.0f - percentage) GammaRatio.x -= Delta; //0.008f;
	if (GammaRatio.y > 1.0f - percentage) GammaRatio.y -= Delta; //0.008f;
	if (GammaRatio.z > 1.0f - percentage) GammaRatio.z -= Delta; //0.008f;
}

void Renderer::ScreenBright()
{
	if (GammaRatio.x < 1) dimmRatio -= Delta;// 0.008f;
	if (GammaRatio.x < 1) GammaRatio.x += Delta; //0.008f;
	if (GammaRatio.y < 1) GammaRatio.y += Delta; //0.008f;
	if (GammaRatio.z < 1) GammaRatio.z += Delta; //0.008f;
}

void Renderer::setTextureCoords(Tile & tile)
{
	GLuint nr = tile.getTextureNumber();
	float offsetx = (float)nr*0.1f;
	float offsety = GLuint(nr / 10)*0.25f;
	// Just for fun
	if (tile.getTextureNumber() == 8) offsety = 0.25f*(rand() % 4);
	_SpriteSheetShader.setFloat("offsetX", offsetx);
	_SpriteSheetShader.setFloat("offsetY", offsety);
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

void Renderer::setTextureCoords(Projectile & proj)
{
	Vec2i pos = proj.getFrame();
	float offsetx = (float)pos._x*0.1f;
	float offsety = (float)pos._y*0.25f;
	_SpriteSheetShader.setFloat("offsetX", offsetx);
	_SpriteSheetShader.setFloat("offsetY", offsety);
}

void Renderer::setTextureCoords(GLuint x)
{
	float offsetx = x*0.1f;
	float offsety = 0.0f;
	_SpriteSheetShader.setFloat("offsetX", offsetx);
	_SpriteSheetShader.setFloat("offsetY", offsety);
}

void Renderer::setTextureCoords(Vec2i pos)
{
	float offsetx = pos._x * 0.1f;
	float offsety = pos._y *0.25f;
	_SpriteSheetShader.setFloat("offsetX", offsetx);
	_SpriteSheetShader.setFloat("offsetY", offsety);
}

void Renderer::setDelta(double delta)
{
	Delta = delta;
}

void Renderer::draw(double x, double y,GLuint IdTexture, double scale)
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

	_SpriteSheetShader.use();
	_SpriteSheetShader.setMat4("model", model);
	glBindVertexArray(*VAO);
	

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}

void Renderer::drawText(double x, double y, GLuint IdTexture, Vec2d scale, glm::vec4 color)
{
	

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-StartPosX, StartPosY, 0.0f));
	model = glm::translate(model, glm::vec3(TranslateValueX*x, -TranslateValueY * y, 0.0f));

	model = glm::scale(model, glm::vec3(scale._x, scale._y , 0.0f));


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, IdTexture);

	_SpriteSheetShader.use();
	_SpriteSheetShader.setMat4("model", model);
	_SpriteSheetShader.setVec4("Gamma", color);
	glBindVertexArray(*VAO);

	
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
		glBindTexture(GL_TEXTURE_2D, doors->getID());

		setTextureCoords((GLuint)DoorState);

		_SpriteSheetShader.use();
		_SpriteSheetShader.setMat4("model", model);
		glBindVertexArray(*VAO);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}
