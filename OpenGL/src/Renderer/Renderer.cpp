#include "Renderer.h"



Renderer::Renderer(const Camera& camera)
	:
	_SpriteSheetShader("src/Shaders/vs.vs", "src/Shaders/fs.fs")
	, cam(camera)
	, dimmRatio(0.0f)
	, _gamestate(nullptr)
	, _maxgamma(1.0)
{
	//Ustawienie gammy na full
	//GammaRatio = glm::vec4(_maxgamma, _maxgamma, _maxgamma, 1.0f);
	GammaRatio = glm::vec4(0, 0, 0, 1.0f);
	

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

	//To ma byæ wywo³ane przed u¿yciem jakiejkolwiek tekstury
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
	_SpriteSheetShader.setVec4("Gamma", GammaRatio);

	if (*_gamestate != State::MAIN_MENU && *_gamestate != State::EXIT && *_gamestate != State::START && *_gamestate != State::CLOSING_MENU)
	{
		RenderMap();
		RenderItems(items);
		RenderCharacters(characters);
		RenderText(text);
	}
	else if (*_gamestate != State::EXIT && *_gamestate != State::CLOSING_GAME)
	{
		RenderMenu();
		RenderText(text);
	}

	
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
	//Rysowanie od ty³u = gracz zawsze na wierzchu
	for(int i = (int)characters.size()-1; i>-1;--i)
	{
			for (int j = (int)characters[i].getPifPafSize() - 1; j > -1; --j)
			{
				if (characters[i].getOnepiFpaF(j).getExistance() == true)
				{
					setTextureCoords(characters[i].getOnepiFpaF(j));
					draw(characters[i].getOnepiFpaF(j)._position.getX(), characters[i].getOnepiFpaF(j)._position.getY(), characters[i].getPifPafTexture(),0.05);
				}
			}
		setTextureCoords(characters[i]);
		draw(characters[i].getPos()._x, characters[i].getPos()._y, characters[i].getTexture(), 0.0, characters[i].getColor());
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

			setTextureCoords((*items)[i]->getID());
			draw((*items)[i]->getX(), (*items)[i]->getY(), (*items)[i]->getTexture());
		}
	}
}

void Renderer::RenderText(const TextGenerator& text)
{

	for (size_t i = 0; i < text.getAmount(); i++)
	{	
		std::string name = text.getName(i);
		if (text.CheckDrawing(name) == true)
		{
			double counter = 0;
			for (auto x : text.getText(name))
			{
				Vec2ic sheetPos = text.getSheetPosition(toupper(x));
				Vec2dc textPos = text.getPosition(name);

				glm::vec4 tempColor = text.getColor(name);
				if (dimmRatio > 0 && text.CheckMenu(name) == true)
				{
					tempColor.r += dimmRatio;
					tempColor.g += dimmRatio;
					tempColor.b += dimmRatio;
				}


				
				if (tempColor.a <= _maxgamma && text.getFinish(name) == false && *_gamestate != State::MENU && *_gamestate != State::PAUSE)
					text.setTransparency(name, tempColor.a += float(0.2f * Delta));
				else if (tempColor.a >= 0.0f && text.getFinish(name) == true && *_gamestate != State::MENU && *_gamestate != State::PAUSE)
					text.setTransparency(name, tempColor.a -= float(0.2f * Delta));

				setTextureCoords(sheetPos);
				drawText(textPos._x + counter*text.getSize(name)._x*5, textPos._y, text.getTexture(), text.getSize(name), tempColor);
				counter++;
			}
	
		}
	}

}

void Renderer::RenderMenu()
{
	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	glm::mat4 model = glm::mat4(1.0f);
	//model = glm::translate(model, glm::vec3(-StartPosX + 1, StartPosY - 1, 0.0f));
	//model = glm::translate(model, glm::vec3(TranslateValueX, -TranslateValueY , 0.0f));
	//model = glm::translate(model, glm::vec3((float)cam.getTranslate()._x, (float)cam.getTranslate()._y, 0.0f));

	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.0f));

	_SpriteSheetShader.setFloat("offsetX", 0.0f);
	_SpriteSheetShader.setFloat("offsetY", 0.0f);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _pictureid);

	_SpriteSheetShader.use();
	_SpriteSheetShader.setMat4("model", model);
	glBindVertexArray(*VAO);


	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void Renderer::ScreenDimm(float percentage)
{
	if (Delta > 1.0) Delta = 0.1;
	if (GammaRatio.x > _maxgamma - percentage) GammaRatio.x -= (float)Delta; 
	if (GammaRatio.y > _maxgamma - percentage) GammaRatio.y -= (float)Delta;
	if (GammaRatio.z > _maxgamma - percentage) GammaRatio.z -= (float)Delta;
}

void Renderer::ScreenDimmWithoutMenu(float percentage)
{
	if (Delta > 1.0) Delta = 0.1;

	if (GammaRatio.x > _maxgamma * (1 - percentage))
	{
		GammaRatio.x -= (float)Delta;
		dimmRatio += (float)Delta;
	}
	if (GammaRatio.y > _maxgamma * ( 1 - percentage) )  GammaRatio.y -= (float)Delta;
	if (GammaRatio.z > _maxgamma * ( 1 - percentage) )  GammaRatio.z -= (float)Delta;
}

void Renderer::ScreenBright()
{
	if (Delta > 1.0) Delta = 0.1;
	if (GammaRatio.x < _maxgamma && dimmRatio > 0) dimmRatio -= (float)Delta;
	else if (dimmRatio < 0) dimmRatio = 0;
	if (GammaRatio.x < _maxgamma) GammaRatio.x += (float)Delta;
	if (GammaRatio.y < _maxgamma) GammaRatio.y += (float)Delta;
	if (GammaRatio.z < _maxgamma) GammaRatio.z += (float)Delta;

	if (GammaRatio.x > _maxgamma)
	{
		dimmRatio = 0;
		GammaRatio.x = (float)_maxgamma + 0.001f;
		GammaRatio.y = (float)_maxgamma + 0.001f;
		GammaRatio.z = (float)_maxgamma + 0.001f;
	}
}

void Renderer::setGamma(double gamma)
{
	_maxgamma = gamma;
	GammaRatio = glm::vec4(_maxgamma, _maxgamma, _maxgamma, 1.0f);
}

void Renderer::GammaUp()
{
	if (_maxgamma < 1.0)
		_maxgamma += 0.05;
	if (_maxgamma > 1.0)
		_maxgamma = 1.0;

	//if (dimmRatio > 0)
	//	dimmRatio += dimmRatio * 0.05;

}

void Renderer::GammaDown()
{
	if (_maxgamma > 0)
		_maxgamma -= 0.05;
	if (_maxgamma < 0)
		_maxgamma = 0;

	//if (dimmRatio > 0)
	//	dimmRatio -= dimmRatio * 0.05;

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

double Renderer::getMaxGamma()
{
	return _maxgamma;
}

void Renderer::setDelta(double delta)
{
	Delta = delta;
}

void Renderer::setPictureId(GLuint id)
{
	_pictureid = id;
}

void Renderer::setGameState(State & gamestate)
{
	_gamestate = &gamestate;
}

void Renderer::draw(double x, double y,GLuint IdTexture, double scale, glm::vec4 color)
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

	float temp = GammaRatio.a;
	GammaRatio.a = color.a;
	
	_SpriteSheetShader.setVec4("Gamma", GammaRatio);
	_SpriteSheetShader.setMat4("model", model);
	glBindVertexArray(*VAO);
	

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	GammaRatio.a = temp;
}

void Renderer::drawSelf(double x, double y, GLuint IdTexture, double scaleX, double scaleY, glm::vec4 color)
{

	//Eksperymentalnie udowodniono ze dziala xD
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(-StartPosX, StartPosY, 0.0f));
	model = glm::translate(model, glm::vec3(TranslateValueX*x, -TranslateValueY * y, 0.0f));


	//Skalowanko lepiej na koncu xD
	model = glm::scale(model, glm::vec3(scaleX > 0 ? scaleX : ScaleFactorX, scaleY > 0 ? scaleY : ScaleFactorY, 0.0f));


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, IdTexture);

	_SpriteSheetShader.use();

	//float temp = GammaRatio.a;
	//GammaRatio.a = color.a;

	_SpriteSheetShader.setVec4("Gamma", glm::vec4(color.r - 1.0 + GammaRatio.r, color.g - 1.0 + GammaRatio.g, color.b - 1.0 + GammaRatio.b, color.a));
	_SpriteSheetShader.setMat4("model", model);
	glBindVertexArray(*VAO);


	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//GammaRatio.a = temp;
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
	//_SpriteSheetShader.setVec4("Gamma", color);
	_SpriteSheetShader.setVec4("Gamma", glm::vec4(color.r - 1.0 + GammaRatio.r, color.g - 1.0 + GammaRatio.g, color.b - 1.0 + GammaRatio.b , color.a) );
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
