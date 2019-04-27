#include "GameEngine.h"

GameEngine::GameEngine()
	:
	  window(nullptr)
	, renderer(nullptr)
	, textGen(nullptr)
	, _Menu(nullptr)
	, t()
	, SCR_WIDTH(800)
	, SCR_HEIGHT(800)
	, lastX(SCR_WIDTH / 2.0)
	, lastY(SCR_HEIGHT / 2.0)
	, firstMouse(true)
	, WindowName("Kacp3r3 & Bartek Playground")
	, camera(6,6)
	, lvlWin(false)
	,_lvlgen("res/Data/map.txt")
	, _gameState(State::MAIN_MENU)
	, _gameDifficulty(Difficulty::BEGIN)
	, soundEngine("res/Data/Sounds/", t)
{
}

void GameEngine::Game_Init()
{

	
	

	
	try {

		//================================================================
		//= Initialize GLFW and force to use 3.3 OpenGL
		//================================================================
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		


		//================================================================
		//= Creating the Window
		//================================================================
		window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "THE GAME !", NULL, NULL);
		//window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "THE GAME !", glfwGetPrimaryMonitor(), NULL);
		if (!window)
		{
			glfwTerminate();
			return; //void nie zwraca  - Twoja stara nie zwraca a nie void
		}

		// Position of the Window
		glfwSetWindowPos(window, 500, 130);

		/* Make the window's context current */
		glfwMakeContextCurrent(window);

		//Fps lock
		//glfwSwapInterval(2);


		//================================================================
		//= Glew Initialization
		//================================================================
		if (glewInit() != GLEW_OK)
			std::cout << "ERROR";


		std::cout << glGetString(GL_VERSION) << std::endl;

		renderer = new Renderer(camera);
		textGen = new TextGenerator(10.0, 10.0, t);
		_Menu = new Menu(soundEngine, _gameState, window , *textGen, *renderer);
		_map = renderer->getMap();
		_map->LoadLevel(_lvlgen.generateLevel(_map->getWidth(), _map->getHeight()));
	}
	catch (std::runtime_error &e)
	{
		std::cout << e.what();
		int a;
		std::cin >> a;
	}

	//PLAYER ADDED HERE
	_characters.push_back(Hero("player", 5.0, 5.0, 3.0, { 0.4,0.75 }, 9));
	_characters.push_back(Enemy("boss", 5.0, 1.0, 1.0, { 0.4,0.8 }, 9));
	_characters.push_back(Enemy("bae",3.0, 5.0, 1.0, { 0.4,0.8 },8));
	_characters.push_back(Enemy("skelly2",1.0, 5.0, 1.0, { 0.4,0.8 },9));
	_characters.push_back(Enemy("boy",5.0, 8.0, 1.0, { 0.4,0.8 },4));


	camera.initCamera(_characters[0].getPos(),_map->getWidth(),_map->getHeight());

	//HARDCODE
	_characters[0].setRange(50);
	Item::_texture = AssetManager::Get().getSprite("items");

	renderer->setGameState(_gameState);

}

void GameEngine::Game_Run()
{

	// Game  Initialization

	Game_Init();



	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window) && _gameState != State::EXIT)
	{

		//Providing delta Time
		t.Mark();
		while (t.getDelta() <= t.getSingleFrameTime())
		{
			t.Mark();
		}

		//Refresh all delay time
		t.refresh(false);
		renderer->setDelta(t.getDelta());

		//Updating Label name
		std::string a = WindowName + " FPS: " + std::to_string((int)round(1 / t.getDelta()));
		glfwSetWindowTitle(window, a.c_str());
		

		// input tylko jak gracz ma cos robic
			// -----
		processInput();
		//BRIGHT IF NOT FULLY BRIGHT
		if (_gameState == State::GAME && !renderer->isBright())
			renderer->ScreenBright();
		if (_gameState == State::MAIN_MENU && !renderer->isBright())
			renderer->ScreenBright();


		//SHOW MENU
		if (_gameState == State::MENU || _gameState == State::MAIN_MENU)
			_Menu->ShowMenu(1.8, 1.3);
		

		//SMOOTH CLOSING GAME
		if (_gameState == State::CLOSING_GAME || _gameState == State::CLOSING_MENU)
		{
			if (!renderer->isDark())
				renderer->ScreenDimm();
			else if (_Menu->ToMainMenu() == false)
				_gameState = State::EXIT;
			else
			{
				HideGUI();
				_Menu->OnMainMenu(true);
				_gameState = State::MAIN_MENU;
			}
		}
		
		


		//SMOOTH MAIN MENU TO GAME
		if (!renderer->isDark() && _gameState == State::START)
			renderer->ScreenDimm(1.0f);
		else 
			if (_gameState == State::START || _gameState == State::GAME)
				_gameState = State::GAME;

		

		//Game Update
		if (_gameState == State::GAME && renderer->isBright())
		{
			//GUI
			
				ShowGUI({ 0,0 });

			t.refresh(true);
			camera.UpdateCamera(_characters[0].getPos(),_characters[0].getOrigin().getSize()/2.0);
			Update();
			ProcessEnemiesMove(t.getDelta()<1.0?t.getDelta():0.01);
		}
		//else if



		//Gdy przejdziemy poziom i wejdziemy w drzwi
		if (_gameState == State::INIT)
		{
			if (lvlWin == true && !renderer->isDark())
			{
				soundEngine.Play("win");
				renderer->ScreenDimm(1.0f);
			}
			else
			{
				if (!renderer->isBright() && lvlWin)
				{
					
					_map->LoadLevel(_lvlgen.generateLevel(_map->getWidth(), _map->getHeight()));
					//Tutaj funkcja do generowanie enemisuf
					_characters.push_back(Enemy("boss", 5.0, 1.0, 1.0, { 0.5,0.9 }, 9));
					_characters.push_back(Enemy("skelly2", 1.0, 5.0, 1.0, { 0.5,0.9 }, 9));
					_characters.push_back(Enemy("bae", 3.0, 5.0, 1.0, { 0.5,0.9 }, 9));
					_characters[0]._position._x = _map->getWidth() / 2;
					_characters[0]._position._y = _map->getHeight() / 2;
					camera.UpdateCamera(_characters[0].getPos(), _characters[0].getOrigin().getSize() / 2.0);
					t.Reset();
					lvlWin = false;
					Doors();
					debuginfo.Init(_characters);
				}
				if(!renderer->isBright())renderer->ScreenBright();
				if (renderer->isBright())
				{
					_gameState = State::GAME;
				}
			}
		}

		
		//Renderowanie ³adnie w jednej funkcji
		renderer->Render(_characters, &_ItemGenerator.getItems(), *textGen);
		soundEngine.Refresh();
	

		//DEBUG STUFF
		updateInfo();
		drawInfo();
		
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	while (!renderer->isDark())
		renderer->ScreenDimm();

	glfwTerminate();
}




void GameEngine::processInput()
{
	if (_gameState != State::INIT)
	{
		//Closing Window
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			if (t.delay("Escape", 0.3, false))
			{
				if (_gameState == State::GAME || _gameState == State::PAUSE)
					_Menu->Open();
				else if (_gameState == State::MENU)
				{
					_gameState = State::GAME;
					_Menu->Close();
				}
				else if (_gameState == State::MAIN_MENU)
				{

				}

			}
			
			//glfwSetWindowShouldClose(window, true);
		}
		if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS)
			soundEngine.VolumeUp();
		if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
			soundEngine.VolumeDown();
		
		if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
		{
			if (t.delay("Enter", 0.3, false))
			{
				if (_gameState == State::GAME)
					_gameState = State::PAUSE;
				else if (_gameState == State::MENU || _gameState == State::MAIN_MENU)
					_Menu->enter();
				else if (_gameState == State::PAUSE)
					_gameState = State::GAME;
			}
		}
		
		
		//if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		//{
		//}
		//if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		//{
		//}



		std::pair<Animation::Direction, Animation::Direction> dirMove{ Animation::Direction::NONE,Animation::Direction::NONE};
		std::pair<Animation::Direction, Animation::Direction> dirShoot{ Animation::Direction::NONE,Animation::Direction::NONE};

		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			//_characters[0].setSide(Animation::UP);
			//ProcessPlayerShoot();
			if (_gameState == State::GAME)
				dirShoot.first = Animation::Direction::UP;
			else if (_gameState == State::MENU || _gameState == State::MAIN_MENU)
			{
				if (t.delay("UP", 0.3, false))
				{
					_Menu->moveUP();
				}
			}
		}
		else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			//_characters[0].setSide(Animation::DOWN);
			//ProcessPlayerShoot();
			if (_gameState == State::GAME)
				dirShoot.first = Animation::Direction::DOWN;
			else if (_gameState == State::MENU || _gameState == State::MAIN_MENU)
			{
				if (t.delay("Down", 0.3, false))
				{
					_Menu->moveDOWN();
				}
			}
		}
		else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			//_characters[0].setSide(Animation::LEFT);
			//ProcessPlayerShoot();
			if (_gameState == State::GAME)
				dirShoot.first = Animation::Direction::LEFT;
			else if (_gameState == State::MENU || _gameState == State::MAIN_MENU)
			{
				if (t.delay("Left", 0.3, false))
				{
					_Menu->MoveLeft();
				}
			}
		}
		else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			//_characters[0].setSide(Animation::RIGHT);
			//ProcessPlayerShoot();
			if (_gameState == State::GAME)
				dirShoot.first = Animation::Direction::RIGHT;
			else if (_gameState == State::MENU || _gameState == State::MAIN_MENU)
			{
				if (t.delay("Right", 0.3, false))
				{
					_Menu->MoveRight();
				}
			}
		}

		// InGame
		if (_gameState == State::GAME)
		{
			//Debug info
			if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
			{
				std::cout << "PlayerX: " << _characters[0].getPos().getX() << '\n';
				std::cout << "PlayerY: " << _characters[0].getPos().getY() << '\n';
				std::cout << "VectorX: " << camera.getTranslate()._x << '\n';
				std::cout << "VectorY: " << camera.getTranslate()._y << '\n';
			}

			//Fun
			if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			//PickupItems
			if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && _gameState == State::GAME)
			{

				if (_canPickup)
				{
					ProcessItemPickup();
				}
			}

			//MovementProcessor
			double deltaTime = t.getDelta();
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			{
				//ProcessPlayerMove(deltaTime, Direction::UP);
				dirMove.first = Animation::Direction::UP;
			}
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			{
				//ProcessPlayerMove(deltaTime, Direction::DOWN);
				dirMove.first = Animation::Direction::DOWN;
			}
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			{
				//ProcessPlayerMove(deltaTime, Direction::LEFT);
				dirMove.second = Animation::Direction::LEFT;
			}
			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			{
				//ProcessPlayerMove(deltaTime, Direction::RIGHT);
				dirMove.second = Animation::Direction::RIGHT;
			}

			if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
			{
				if (t.delay("PickUP", 1, true))
					ProcessItemPickup();
			}
			_characters[0].setSide((Animation::Direction)dirShoot.first);
			ProcessPlayerMove(deltaTime, dirMove);
			ProcessPlayerShoot();
		}
	}

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void GameEngine::framebuffer_size_callback(int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void GameEngine::mouse_callback(double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	double xoffset = xpos - lastX;
	double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	//camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void GameEngine::scroll_callback(double xoffset, double yoffset)
{
	//camera.ProcessMouseScroll(yoffset);
}

void GameEngine::initInfo()
{

	//debuginfo.Init(_characters);
}

void GameEngine::updateInfo()
{
	//debuginfo.Update(_characters);
}

void GameEngine::drawInfo()
{
	//debuginfo.Draw();
}

void GameEngine::ProcessPlayerMove(double deltaTime, std::pair<Animation::Direction, Animation::Direction> dir)
{
	//Zmienne upraszczaj¹ce kod
	double px = _characters[0]._position._x;
	double py = _characters[0]._position._y;
	double pv = _characters[0].getVelocity();
	double newX = px;
	double newY = py;

	//Ustaw flage na 0
	_canPickup = false;

	switch (dir.first)
	{
		case Animation::Direction::UP:
		{
			newY -= deltaTime * pv;
			_characters[0].setCurrVelocity(0, -pv);
			break;
		}
		case Animation::Direction::DOWN:
		{
			newY += deltaTime * pv;
			_characters[0].setCurrVelocity(0,  pv);
			break;
		}
		case Animation::Direction::NONE:
		{
			_characters[0].setCurrVelocityY(0);
		}
	}

	switch (dir.second)
	{
		case Animation::Direction::LEFT:
		{
			newX -= deltaTime * pv;
			_characters[0].setCurrVelocity(-pv, 0);
			break;
		}
		case Animation::Direction::RIGHT:
		{
			newX += deltaTime * pv;
			_characters[0].setCurrVelocity(pv, 0);
			break;
		}
		case Animation::Direction::NONE:
		{
			_characters[0].setCurrVelocityX(0);
		}
	}

	if (newX < 0)newX = 0;
	if (newY < 0)newY = 0;

	//CheckColissions(_characters[0], 0, newX, newY);
	_characters[0].updateAnimation({ Animation::Direction(dir.first),Animation::Direction(dir.second) }, deltaTime);

	if (!CheckColissions(_characters[0], 0, newX, newY))
	{
		_characters[0].setX(newX);
		_characters[0].setY(newY);
	}
	else if (!CheckColissions(_characters[0], 0, px, newY))
	{
		_characters[0].setY(newY);
	}
	else if (!CheckColissions(_characters[0], 0, newX,py))
	{
		_characters[0].setX(newX);
	}

	//Czy pozycja gracza == pozycja drzwi

	GLuint x = (GLuint)floor(_map->getWidth() / 2.0);
	GLuint y = (GLuint)floor(_map->getHeight() / 2.0);
	
		//drzwi lewe
	if (_characters[0].getPos().getX() < 0.1 && _characters[0].getPos().getY() > y - 0.2 && _characters[0].getPos().getY() < y + 0.2 && lvlWin == true)
	{
		_gameState = State::INIT;
	}
		//drzwi gorne
	else if (_characters[0].getPos().getX() > x - 0.2 && _characters[0].getPos().getX() < x + 0.2 && _characters[0].getPos().getY() < 0.1 && lvlWin == true)
	{
		_gameState = State::INIT;
	}
		//drzwi prawe
	else if (_characters[0].getPos().getX() > _map->getWidth() - 1.2 && _characters[0].getPos().getY() > y - 0.2 && _characters[0].getPos().getY() < y + 0.2 && lvlWin == true)
	{
		_gameState = State::INIT;

	}



}


void GameEngine::ProcessItemPickup()
{
	double px = _characters[0]._position._x;
	double py = _characters[0]._position._y;

	GLuint nearestid=-1;
	double distance=100.0;
	for (GLuint i = 0; i < _ItemGenerator.getItems().size(); ++i)
	{
		if (_ItemGenerator.getItems()[i]->getOnMap())
		{
			double localdist = abs(_ItemGenerator.getItems()[i]->getX() - px) + abs(_ItemGenerator.getItems()[i]->getY() - py);
			if (localdist < distance)
			{
				distance = localdist;
				nearestid = i;
			}
		}
	}
	
	if (nearestid != -1)
	{
		auto item = _ItemGenerator.getItems()[nearestid];
		textGen->setText(item->sName, item->sName, { camera.getFov()._x/2.0, 2 }, 1);
		textGen->setText(item->sName+"desc", item->getDescription(), { camera.getFov()._x / 2.0, 5 }, 1);
		_characters[0].consumeItem(item);
		_ItemGenerator.getItems()[nearestid]->setOnMap(false);
	}


}

void GameEngine::ProcessPlayerShoot()
{
	double px = _characters[0]._position._x;
	double py = _characters[0]._position._y;
	
	Animation::Direction  pdir = _characters[0].getSide();
	std::vector<Projectile>& temp = _characters[0].getpiFpaF();



	if (t.delay("Shoot", 0, true))
	{
		switch (pdir)
		{
		case Animation::Direction::UP:
		{
			temp.emplace_back(Vec2d(0.2,0.2), px, py - 0.1, 2, 0, Animation::Direction::UP, true, _characters[0].getCurrVelocity(),6);
			break;
		}
		case Animation::Direction::DOWN:
		{
			temp.emplace_back(Vec2d(0.2, 0.2), px, py + 0.1, 2, 0, Animation::Direction::DOWN, true, _characters[0].getCurrVelocity(),6);
			break;
		}
		case Animation::Direction::LEFT:
		{
			temp.emplace_back(Vec2d(0.2, 0.2), px - 0.1, py-0.1, 2, 0, Animation::Direction::LEFT, true, _characters[0].getCurrVelocity(),6);
			break;
		}
		case Animation::Direction::RIGHT:
		{
			temp.emplace_back(Vec2d(0.2, 0.2), px + 0.1, py-0.1, 2, 0, Animation::Direction::RIGHT, true, _characters[0].getCurrVelocity(),6);
			break;
		}

		}
	}
}


void GameEngine::Update()
{
	// Update pociskow
	std::vector<Projectile>& temp = _characters[0].getpiFpaF();
	double deltaTime = t.getDelta();


	for (int i = 0; i < temp.size(); i++)
	{
		Animation::Direction pdir = temp[i].getSide();
		
		double tempV = temp[i].Velocity;
		Vec2d pvel = temp[i].getObjVel();

		Animation::Direction p[2];
		p[0] = pvel._y > 0 ? Animation::Direction::DOWN : Animation::Direction::UP;
		p[1] = pvel._x > 0 ? Animation::Direction::RIGHT : Animation::Direction::LEFT;

		pvel._x = abs(pvel._x);
		pvel._y = abs(pvel._y);

		for (GLuint j = 0; j < 2; ++j)
		{
			if (p[j] == Animation::Direction::NONE) continue;

			if (pdir == Animation::Direction::LEFT && p[j] == Animation::Direction::LEFT) tempV += pvel._x;
			else if (pdir == Animation::Direction::LEFT && p[j] == Animation::Direction::RIGHT) (tempV > pvel._x / 4) ? tempV -= pvel._x / 4 : tempV;

			else if (pdir == Animation::Direction::RIGHT && p[j] == Animation::Direction::LEFT) (tempV > pvel._x / 4) ? tempV -= pvel._x / 4 : tempV;
			else if (pdir == Animation::Direction::RIGHT && p[j] == Animation::Direction::RIGHT) tempV += pvel._x;

			else if (pdir == Animation::Direction::UP && p[j] == Animation::Direction::UP) tempV += pvel._y;
			else if (pdir == Animation::Direction::UP && p[j] == Animation::Direction::DOWN) (tempV > pvel._x / 4) ? tempV -= pvel._x / 4 : tempV;

			else if (pdir == Animation::Direction::DOWN && p[j] == Animation::Direction::UP) (tempV > pvel._x / 4) ? tempV -= pvel._x / 4 : tempV;
			else if (pdir == Animation::Direction::DOWN && p[j] == Animation::Direction::DOWN) tempV += pvel._y;
		}

		
		if (temp[i].getElapdedDistance() < _characters[0].getRange() / 10)
		{
			temp[i].UpdateAnimation(deltaTime);
			switch (pdir)
			{
				case Animation::Direction::UP:
				{
					temp[i]._position.setY(temp[i]._position.getY() - deltaTime * tempV) ;
					temp[i].setElapsedDistance(temp[i].getElapdedDistance() + deltaTime * tempV);
					break;
				}
				case Animation::Direction::DOWN:
				{
					temp[i]._position.setY(temp[i]._position.getY ()+deltaTime * tempV) ;
					temp[i].setElapsedDistance(temp[i].getElapdedDistance() + deltaTime * tempV);
					break;
				}
				case Animation::Direction::LEFT:
				{
					temp[i]._position.setX(temp[i]._position.getX()- deltaTime * tempV) ;
					temp[i].setElapsedDistance(temp[i].getElapdedDistance() + deltaTime * tempV);
					break;
				}
				case Animation::Direction::RIGHT:
				{
					temp[i]._position.setX(temp[i]._position.getX() + deltaTime * tempV) ;
					temp[i].setElapsedDistance(temp[i].getElapdedDistance() + deltaTime * tempV);
					break;
				}
				
			}
			if (CheckCollisionsBullet(temp[i], 0, temp[i].getX(), temp[i].getY()))
			{
				temp[i].setExistance(false);
				temp.erase(temp.begin() + i);
				i -= 1;
			}

		}
		else
		{
			temp[i].setExistance(false);
			temp.erase(temp.begin() + i);
		}
	}
}

void GameEngine::ShowGUI(Vec2d position)
{
	Vec2d scale = position;
	scale._x = (0.3 + position._x - 1) / 2;
	scale._y = (0.3  + position._y - 1) / 2;
	double offsetX = 1.0;
	double offsetY = 0.3;


	// HP
	textGen->setText("HP", "HP ", Vec2d(scale._x, scale._y), 0, Vec2d(0.03, 0.05));
	textGen->setInfinity("HP", true);
	textGen->setText("HP VALUE", std::to_string((GLuint)_characters[0].getHealth()), Vec2d(scale._x + offsetX, scale._y), 0, Vec2d(0.05, 0.04));
	textGen->setInfinity("HP VALUE", true);
	// RANGE
	textGen->setText("RANGE", "RANGE ", Vec2d(scale._x, scale._y + 1 * offsetY), 0, Vec2d(0.03, 0.05));
	textGen->setInfinity("RANGE", true);
	textGen->setText("RANGE VALUE", std::to_string((GLuint)_characters[0].getRange()) , Vec2d(scale._x + offsetX, scale._y + 1 * offsetY), 0, Vec2d(0.05, 0.04));
	textGen->setInfinity("RANGE VALUE", true);

	// SPEED
	textGen->setText("SPEED", "SPEED ", Vec2d(scale._x, scale._y + 2 * offsetY), 0, Vec2d(0.03, 0.05));
	textGen->setInfinity("SPEED", true);
	textGen->setText("SPEED VALUE", std::to_string((GLuint)_characters[0].getMovementSpeed()) , Vec2d(scale._x + offsetX, scale._y + 2 * offsetY), 0, Vec2d(0.05, 0.04));
	textGen->setInfinity("SPEED VALUE", true);

	// ATT S
	textGen->setText("ATTACKS", "ATT S ", Vec2d(scale._x, scale._y + 3 * offsetY), 0, Vec2d(0.03, 0.05));
	textGen->setInfinity("ATTACKS", true);
	textGen->setText("ATTACK VALUE", std::to_string((GLuint)_characters[0].getAttackSpeed()) , Vec2d(scale._x + offsetX, scale._y + 3 * offsetY), 0, Vec2d(0.05, 0.04));
	textGen->setInfinity("ATTACK VALUE", true);

	// DMG
	textGen->setText("DMG", "DMG ", Vec2d(scale._x, scale._y + 4 * offsetY), 0, Vec2d(0.03, 0.05));
	textGen->setInfinity("DMG", true);
	textGen->setText("DMG VALUE", std::to_string((GLuint)_characters[0].getDamage()) , Vec2d(scale._x + offsetX, scale._y + 4 * offsetY), 0, Vec2d(0.05, 0.04));
	textGen->setInfinity("DMG VALUE", true);
}

void GameEngine::HideGUI()
{
	textGen->setInfinity("HP", false);
	textGen->setInfinity("HP VALUE", false);

	textGen->setInfinity("RANGE", false);
	textGen->setInfinity("RANGE VALUE", false);

	textGen->setInfinity("SPEED", false);
	textGen->setInfinity("SPEED VALUE", false);

	textGen->setInfinity("ATTACKS", false);
	textGen->setInfinity("ATTACK VALUE", false);

	textGen->setInfinity("DMG", false);
	textGen->setInfinity("DMG VALUE", false);
}

void GameEngine::ProcessEnemiesMove(double deltaTime)
{
	//Zmienne upraszczaj¹ce kod
	double px = _characters[0]._position._x;
	double py = _characters[0]._position._y;
	for (GLuint i = 1; i < (GLuint)_characters.size(); ++i)
	{
		double mx = _characters[i]._position._x;
		double my = _characters[i]._position._y;
		double mv = _characters[i].getVelocity();
		Vec2d Move(mx - px, my - py);
		
		//Potrzebne zmienne
		bool move1 = true;
		bool move2 = true;
		double newX = mx;
		double newY = my;


		//Trochê Matmy
		double VelLength = Move.getLength();
		double HowMuchInX = abs(Move.getX() / VelLength);
		double HowMuchInY = abs(Move.getY() / VelLength);


		//Rozpatrzmy kierunki
		Animation::Direction dir[2];
		dir[0] = CalculateDirection(Move._x, false, 0.03);
		dir[1] = CalculateDirection(Move._y,true,0.03);

		for(GLuint i=0;i<2;i++)
		{
			switch (dir[i])
			{
			case Animation::Direction::UP:
			{
				newY -= deltaTime * mv * HowMuchInY;
				break;
			}
			case Animation::Direction::DOWN:
			{
				newY += deltaTime * mv* HowMuchInY;
				break;
			}
			case Animation::Direction::LEFT:
			{
				newX -= deltaTime * mv* HowMuchInX;
				break;
			}
			case Animation::Direction::RIGHT:
			{
				newX += deltaTime * mv* HowMuchInX;
				break;
			}
			case Animation::Direction::NONE:
			{
				break;
			}
			}
		}

		//Safety checks
		if (newY < 0)newY = 0;
		if (newX < 0)newX = 0;
		if (newX > _map->getWidth() - 1) newX = _map->getWidth();
		if (newY > _map->getHeight() - 1) newY = _map->getHeight();
		//Check in X
		move1 = !CheckColissions(_characters[i], i, newX, my);
		//Check in Y
		move2 = !CheckColissions(_characters[i], i, mx, newY);

		//Wykonaj ruch
			if (move1 && newX!=mx)
			{
				//Je¿eli w drug¹ stronie nie ma ruchu
				if (!move2)
				{
					//Policz czy jest sens i dodaj do pierwotnego kierunku
					double value = mv * deltaTime;
					if (dir[0] == Animation::Direction::LEFT)
					{
						if(!CheckColissions(_characters[i],i,mx-value,my)) newX = mx-value;
					}
					else
					{
						if (!CheckColissions(_characters[i], i, mx + value, my)) newX = mx+ value;
					}
				}
				_characters[i].setX(newX);
				
				if (HowMuchInY < HowMuchInX )_characters[i].updateAnimation({ Animation::Direction::NONE,(Animation::Direction)dir[0]}, deltaTime);
			}
			if (move2&&newY!=my)
			{
				if (!move1)
				{
					double value = mv * deltaTime;
					if (dir[1] == Animation::Direction::UP)
					{
						if (!CheckColissions(_characters[i], i, mx, my-value)) newY = my-value;
					}
					else
					{
						if (!CheckColissions(_characters[i], i, mx, my+value)) newY = my+value;
					}
					//_characters[i].updateAnimation({ (Animation::Direction)dir[1],Animation::Direction::NONE }, deltaTime);
				}
				_characters[i].setY(newY);
				
				if(HowMuchInY>HowMuchInX)_characters[i].updateAnimation({ (Animation::Direction)dir[1],Animation::Direction::NONE }, deltaTime);
			}
	}
	
}

void GameEngine::Doors()
{
	GLuint x = (GLuint)ceil(_map->getWidth() / 2.0) - 1;
	GLuint y = (GLuint)ceil(_map->getHeight() / 2.0) - 1;
	GLuint id[] = { x,0,0,y,_map->getWidth() - 1,y };

	if (lvlWin)
	{
		for (GLuint i = 0; i < 6; i += 2)
		{
			_map->getTile(id[i], id[i + 1]).setSolid(false);
		}
		renderer->OpenDoors();
		_ItemGenerator.GenerateItem(5, 6);
	}

	else
	{
		for (GLuint i = 0; i < 6; i += 2)
		{
			_map->getTile(id[i], id[i + 1]).setSolid(true);
		}
		renderer->CloseDoors();
	}

}

Animation::Direction GameEngine::CalculateDirection(double x, bool pionowo, double margin)
{
	if (!pionowo)
	{
		if (abs(x) > margin)
		{
			if (x > 0) return Animation::Direction::LEFT;
			else return  Animation::Direction::RIGHT;
		}
		else return  Animation::Direction::NONE;
	}
	else
	{
		if (abs(x) > margin)
		{
			if (x > 0) return Animation::Direction::UP;
			else return Animation::Direction::DOWN;
		}
		else return  Animation::Direction::NONE;
	}
}

bool GameEngine::CheckColissions(Character & obj, GLuint index, double x, double y)
{
	//Some utility variables
	auto getIndex = [&](GLuint x, GLuint y) { return y * _map->getWidth() + x; };
	GLuint xx = (GLuint)floor(x);
	GLuint yy = (GLuint)floor(y);
	//Safety checks
	if (xx < 1)xx = 1;
	if (yy < 1)yy = 1;
	//if (xx + 2 > _map->getWidth())xx = _map->getWidth() - 1;
	//if (yy + 2 > _map->getHeight())yy = _map->getHeight() - 1;

	//Check map Around Character
	std::vector<GLuint>indexesToCheck = {getIndex(xx-1,yy-1),getIndex(xx,yy-1),getIndex(xx+1,yy - 1),
								  getIndex(xx - 1,yy),getIndex(xx,yy),getIndex(xx + 1,yy),
								  getIndex(xx - 1,yy + 1),getIndex(xx,yy + 1),getIndex(xx + 1,yy + 1) };
	std::vector<GLuint>indexes;
	Origin tmp = Origin(4, obj.getOrigin().getSize(), Vec2d(x, y));
	for (GLuint i = 0; i < indexesToCheck.size(); ++i)
	{
		if (ShapeOverlap_DIAGS(tmp, _map->getTile((GLuint)indexesToCheck[i]).getOrigin()))
		{
			indexes.push_back(indexesToCheck[i]);
		}
	}

	for (GLuint i = 0; i < indexes.size(); ++i)
	{
		//std::cout << "Kolizja!" << '\n';
		if (_map->getTile(indexes[i]).GetSolid()) return true;
	}

	//a teraz kolizje z innymi characterami
	for (GLuint j = 0; j < _characters.size(); ++j)
	{
		if (j != index) if (ShapeOverlap_DIAGS(tmp, _characters[j].getOrigin())) return true;
	}

	return false;
}

//One Lone Coder Overlapping Algorithm
bool GameEngine::ShapeOverlap_DIAGS(Origin &r1, Origin &r2)
{
	Origin *poly1 = &r1;
	Origin *poly2 = &r2;

	for (int shape = 0; shape < 2; shape++)
	{
		if (shape == 1)
		{
			poly1 = &r2;
			poly2 = &r1;
		}

		// Check diagonals of polygon...
		for (GLuint p = 0; p < poly1->getVertexCount(); p++)
		{
			Vec2d line_r1s = poly1->getCenter();
			Vec2d line_r1e = poly1->getVertex(p);

			// ...against edges of the other
			for (GLuint q = 0; q < poly2->getVertexCount(); q++)
			{
				Vec2d line_r2s = poly2->getVertex(q);
				Vec2d line_r2e = poly2->getVertex((q + 1) % poly2->getVertexCount());

				// Standard "off the shelf" line segment intersection
				double h = (line_r2e.getX() - line_r2s.getX()) * (line_r1s.getY() - line_r1e.getY()) - (line_r1s.getX() - line_r1e.getX()) * (line_r2e.getY() - line_r2s.getY());
				double t1 = ((line_r2s.getY() - line_r2e.getY()) * (line_r1s.getX() - line_r2s.getX()) + (line_r2e.getX() - line_r2s.getX()) * (line_r1s.getY() - line_r2s.getY())) / h;
				double t2 = ((line_r1s.getY() - line_r1e.getY()) * (line_r1s.getX() - line_r2s.getX()) + (line_r1e.getX() - line_r1s.getX()) * (line_r1s.getY() - line_r2s.getY())) / h;

				if (t1 >= 0.0f && t1 < 1.0f && t2 >= 0.0f && t2 < 1.0f)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool GameEngine::CheckCollisionsBullet(Projectile & bullet, GLuint index, double x, double y)
{
	//Some utility variables
	auto getIndex = [&](int x, int y) -> int { return y * _map->getWidth() + x; };
	int xx = (int)floor(x);
	int yy = (int)floor(y);
	//Safety checks
	if (xx < 1)xx = 1;
	if (yy < 1)yy = 1;
	//if (xx + 2 > _map->getWidth())xx = _map->getWidth() - 1;
	//if (yy + 2 > _map->getHeight())yy = _map->getHeight() - 1;

	//Check map Around Character
	std::vector<int>indexesToCheck = { getIndex(xx - 1,yy - 1),getIndex(xx,yy - 1),getIndex(xx + 1,yy - 1),
								  getIndex(xx - 1,yy),getIndex(xx,yy),getIndex(xx + 1,yy),
								  getIndex(xx - 1,yy + 1),getIndex(xx,yy + 1),getIndex(xx + 1,yy + 1) };
	std::vector<GLuint>indexes;
	Origin tmp((GLuint)4,bullet.getOrigin().getSize(), Vec2d(x, y));
	for (GLuint i = 0; i < indexesToCheck.size(); ++i)
	{
		if (ShapeOverlap_DIAGS(tmp, _map->getTile(indexesToCheck[i]>0?indexesToCheck[i]:0).getOrigin()))
		{
			indexes.push_back(indexesToCheck[i]);
		}
	}

	for (GLuint i = 0; i < indexes.size(); ++i)
	{
		//std::cout << "Kolizja!" << '\n';
		if (_map->getTile(indexes[i]).GetSolid()) return true;
	}

	//a teraz kolizje z innymi characterami
	for (GLuint j = 1; j < _characters.size(); ++j)
	{
		if (ShapeOverlap_DIAGS(tmp, _characters[j].getOrigin()))
		{
			soundEngine.Play("hit");
			if (_characters[j].TakeDamage(bullet))
			{
				_characters.erase(_characters.begin() + j);
				j -= 1;

				//Win condition check
				if (_characters.size() == 1)
				{
					lvlWin = true;
					Doors();
				}
				
			}
			return true;
		}
	}

	return false;
}
