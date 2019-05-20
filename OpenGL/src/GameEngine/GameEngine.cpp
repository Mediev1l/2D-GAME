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
	, soundEngine("res/Data/Sounds/","sounds.txt", t)
	, effectEngine("res/Data/Sounds/","effects.txt", t)
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
		_Menu = new Menu(soundEngine, effectEngine, _gameState, window , *textGen, *renderer);
		_map = renderer->getMap();
		_map->LoadLevel(_lvlgen.generateLevel(_map,_gameDifficulty));
	}
	catch (std::runtime_error &e)
	{
		std::cout << e.what();
		int a;
		std::cin >> a;
	}

	//PLAYER ADDED HERE
	Character::t = &t;
	_characters.push_back(Hero("player", 5.0, 5.0, 3.0, { 0.4,0.75 }, 9));
	GenNextLevel();
	_characters[0].setTimer("puntouch", 2.0);
	_characters[0].setDamage(50);
	_characters[0].setAttackSpeed(0.25);

	//GUI INITIALIZATION
	// HP
	textGen->setText("HP", "HP ", Vec2d(0, 0), 0, Vec2d(0.03, 0.05));
	textGen->setText("HP VALUE", std::to_string((GLuint)_characters[0].getHealth()), Vec2d(0, 0), 0, Vec2d(0.05, 0.04));
	textGen->setInfinity("HP", false);
	textGen->setInfinity("HP VALUE", false);
	// RANGE
	textGen->setText("RANGE", "RANGE ", Vec2d(0, 0), 0, Vec2d(0.03, 0.05));
	textGen->setText("RANGE VALUE", std::to_string((GLuint)_characters[0].getRange()), Vec2d(0, 0), 0, Vec2d(0.05, 0.04));
	textGen->setInfinity("RANGE", false);
	textGen->setInfinity("RANGE VALUE", false);

	// SPEED
	textGen->setText("SPEED", "SPEED ", Vec2d(0, 0), 0, Vec2d(0.03, 0.05));
	textGen->setText("SPEED VALUE", std::to_string((GLuint)_characters[0].getMovementSpeed()), Vec2d(0, 0), 0, Vec2d(0.05, 0.04));
	textGen->setInfinity("SPEED", false);
	textGen->setInfinity("SPEED VALUE", false);

	// ATT S
	textGen->setText("ATTACKS", "ATT S ", Vec2d(0, 0), 0, Vec2d(0.03, 0.05));
	textGen->setText("ATTACK VALUE", std::to_string((GLuint)_characters[0].getAttackSpeed()), Vec2d(0, 0), 0, Vec2d(0.05, 0.04));
	textGen->setInfinity("ATTACKS", false);
	textGen->setInfinity("ATTACK VALUE", false);

	// DMG
	textGen->setText("DMG", "DMG ", Vec2d(0, 0), 0, Vec2d(0.03, 0.05));
	textGen->setText("DMG VALUE", std::to_string((GLuint)_characters[0].getDamage()), Vec2d(0, 0), 0, Vec2d(0.05, 0.04));
	textGen->setInfinity("DMG", false);
	textGen->setInfinity("DMG VALUE", false);


	camera.initCamera(_characters[0].getPos(),_map->getWidth(),_map->getHeight());

	//HARDCODE
	_characters[0].setRange(50);
	Item::_texture = AssetManager::Get().getSprite("items");

	renderer->setGameState(_gameState);
	initInfo();
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
	//	textGen->setText("fps", "FPS: " + (std::to_string(1/t.getDelta())), Vec2d(3,0), 0, Vec2d(0.03, 0.05));

		// input tylko jak gracz ma cos robic
			// -----
		processInput();

		
		//IF NOT FULLY BRIGHT
		if (_gameState == State::GAME && !renderer->isBright())
			renderer->ScreenBright();
		if (_gameState == State::MAIN_MENU && !renderer->isBright() && _Menu->getDimm() != true)
			renderer->ScreenBright();

		//IF VOLUME NOT ON MAX
		if (_Menu->getSoundStatus() == false)
			if (soundEngine.isPlaying() == false || soundEngine.isFull() == false)
				soundEngine.UpToMax();




		//SHOW MENU
		if (_gameState == State::MENU || _gameState == State::MAIN_MENU)
		{
			//ShowGUI({ 0,0 });
			_Menu->ShowMenu(1.8, 1.3);
		}
		

		//SMOOTH CLOSING GAME
		if (_gameState == State::CLOSING_GAME || _gameState == State::CLOSING_MENU)
		{
			if (!renderer->isDark())
			{
				renderer->ScreenDimm();
				soundEngine.DownToZero();
			}
			else if (_Menu->ToMainMenu() == false)
				_gameState = State::EXIT;
			else
			{
				HideGUI();
				HideText();
				_Menu->OnMainMenu(true);
				_Menu->setSoundStatus(false);
				_Menu->ChangeMusic();
				_gameState = State::MAIN_MENU;
			}
		}
		
		


		//SMOOTH MAIN MENU TO GAME
		if (!renderer->isDark() && _gameState == State::START)
		{
			renderer->ScreenDimm(1.0f);
			soundEngine.DownToZero();
		}
		else
		{
			if (_gameState == State::START || _gameState == State::GAME)
			{
				_gameState = State::GAME;
				if (_Menu->getSoundStatus())
				{
					_Menu->ChangeMusic();
					_Menu->setSoundStatus(false);
				}
			}

		}


		//Game Update
		if (_gameState == State::GAME && renderer->isBright())
		{
			//GUI
			
				ShowGUI({ 0,0 });

			t.refresh(true);
			camera.UpdateCamera(_characters[0].getPos(),_characters[0].getOrigin().getSize()/2.0);
			Update();
			ProcessEnemiesMove(t.getDelta()<1.0?t.getDelta():0.01);

			if (!_characters[0].isTouchable() || _characters[0].isTransparent())
				_characters[0].Blink();
			
			
		}
		//else if



		//Gdy przejdziemy poziom i wejdziemy w drzwi
		if (_gameState == State::INIT)
		{
			if (lvlWin == true && !renderer->isDark())
			{
				effectEngine.Play("win");
				renderer->ScreenDimm(1.0f);
			}
			else
			{
				if (!renderer->isBright() && lvlWin) GenNextLevel();
				if(!renderer->isBright())renderer->ScreenBright();
				if (renderer->isBright())
				{
					_gameState = State::GAME;
				}
			}
		}

		if (_gameState==State::GAMEOVER)
		{

			//_Menu->Open();
			_Menu->ShowMenu(1.8, 1.3);
			_map->LoadLevel(_lvlgen.generateLevel(_map,_gameDifficulty));
			//Tutaj funkcja do generowanie enemisuf
			_characters.clear();
			_characters.push_back(Hero("player", _map->getWidth()/2, _map->getHeight()/2, 3.0, { 0.4,0.75 }, 9));
			_characters.push_back(Enemy("boss", 5.0, 1.0, 1.0, { 0.5,0.9 }, 9));
			_characters.push_back(Enemy("skelly2", 1.0, 5.0, 1.0, { 0.5,0.9 }, 9));
			_characters.push_back(Enemy("bae", 3.0, 5.0, 1.0, { 0.5,0.9 }, 9));
			_characters[0]._position._x = _map->getWidth() / 2;
			_characters[0]._position._y = _map->getHeight() / 2;
			camera.UpdateCamera(_characters[0].getPos(), _characters[0].getOrigin().getSize() / 2.0);
			t.Reset();
			lvlWin = false;
			//Doors();
			debuginfo.Init(_characters);
			_gameState = State::MAIN_MENU;
		}


		//Renderowanie ³adnie w jednej funkcji
		renderer->Render(_characters, &_ItemGenerator.getItems(), *textGen);
		soundEngine.Refresh();
		effectEngine.Refresh();
	

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
		
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		{
			_characters[0].getHealth() += 500;
		}

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
			//ProcessShoot();
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
			//ProcessShoot();
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
			//ProcessShoot();
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
			//ProcessShoot();
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
		if (_gameState == State::GAME && renderer->isBright())
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
			ProcessShoot(_characters[0]);
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

	debuginfo.Init(_characters);
}

void GameEngine::updateInfo()
{
	debuginfo.Update(_characters);
}

void GameEngine::drawInfo()
{
	debuginfo.Draw();
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

	int Both = CheckColissions(_characters[0], 0, newX, newY);
	int axisY = CheckColissions(_characters[0], 0, px, newY);
	int axisX = CheckColissions(_characters[0], 0, newX, py);
	if (Both==-1 || (!_characters[0].isTouchable() && Both!=0))
	{
		_characters[0].setX(newX);
		_characters[0].setY(newY);
	}
	else
	{
		if (Both != 0)
		{
			if (_characters[0].isTouchable())
			{
				effectEngine.Play("hit");
				_characters[0].getHealth() -= (long)ceil(_characters[Both].getDamage());
				_characters[0].Untouchable();
			}

		}
	}
	if (axisY==-1|| ( !_characters[0].isTouchable() && axisY != 0))
	{
		_characters[0].setY(newY);
	}
	else
	{
		if (axisY != 0)
		{
			if (_characters[0].isTouchable())
			{
				effectEngine.Play("hit");
				_characters[0].getHealth() -= (long)ceil(_characters[axisY].getDamage());
				_characters[0].Untouchable();
			}
		}
	}
	if (axisX==-1 || (!_characters[0].isTouchable() && axisX != 0))
	{
		_characters[0].setX(newX);
	}
	else
	{
		if (axisX != 0)
		{
			if (_characters[0].isTouchable())
			{
				effectEngine.Play("hit");
				_characters[0].getHealth() -= (long)ceil(_characters[axisX].getDamage());
				_characters[0].Untouchable();
			}
		}
	}

	if (_characters[0].getHealth() <= 0) _gameState = State::GAMEOVER;

	//Czy pozycja gracza == pozycja drzwi

	GLuint x = (GLuint)ceil(_map->getWidth() / 2.0)-1;
	GLuint y = (GLuint)ceil(_map->getHeight() / 2.0)-1;
	
		//drzwi lewe
	if (_characters[0].getPos().getX() < 0.1 && _characters[0].getPos().getY() > y - 0.2 && _characters[0].getPos().getY() < y + 0.2 && lvlWin == true)
	{
		_gameState = State::INIT;
		_gameDifficulty = EASY;
	}
		//drzwi gorne
	else if (_characters[0].getPos().getX() > x - 0.2 && _characters[0].getPos().getX() < x + 0.2 && _characters[0].getPos().getY() < 0.1 && lvlWin == true)
	{
		_gameState = State::INIT;
		_gameDifficulty = Difficulty::MEDIUM;

	}
		//drzwi prawe
	else if (_characters[0].getPos().getX() > _map->getWidth() - 1.2 && _characters[0].getPos().getY() > y - 0.2 && _characters[0].getPos().getY() < y + 0.2 && lvlWin == true)
	{ 
		_gameState = State::INIT;
		_gameDifficulty = HARD;
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
		if (ShapeOverlap_DIAGS(_characters[0].getOrigin(), item->getOrigin() ))
		{
			textGen->setText(item->sName, item->sName, { camera.getFov()._x / 2.0, 2 }, 1);
			textGen->setText(item->sName + "desc", item->getDescription(), { camera.getFov()._x / 2.0, 5 }, 1);
			_characters[0].consumeItem(item);
			_ItemGenerator.getItems()[nearestid]->setOnMap(false);
		}
	}


}

void GameEngine::ProcessShoot(Character& ch)
{
	double px = ch._position._x;
	double py = ch._position._y;
	
	Animation::Direction  pdir = ch.getSide();
	std::vector<Projectile>& temp = ch.getpiFpaF();



	if (t.delay("Shoot"+ch.sName, ch.getAttackSpeed(), true))
	{
		switch (pdir)
		{
		case Animation::Direction::UP:
		{
			temp.emplace_back(Vec2d(0.2, 0.2), px, py - 0.1, 2, 0, Animation::Direction::UP, true, ch.getCurrVelocity(), 6, ch.getDamage());
			break;
		}
		case Animation::Direction::DOWN:
		{
			temp.emplace_back(Vec2d(0.2, 0.2), px, py + 0.1, 2, 0, Animation::Direction::DOWN, true, ch.getCurrVelocity(),6, ch.getDamage());
			break;
		}
		case Animation::Direction::LEFT:
		{
			temp.emplace_back(Vec2d(0.2, 0.2), px - 0.1, py-0.1, 2, 0, Animation::Direction::LEFT, true, ch.getCurrVelocity(),6, ch.getDamage());
			break;
		}
		case Animation::Direction::RIGHT:
		{
			temp.emplace_back(Vec2d(0.2, 0.2), px + 0.1, py-0.1, 2, 0, Animation::Direction::RIGHT, true, ch.getCurrVelocity(),6, ch.getDamage());
			break;
		}

		}
	}
}


void GameEngine::Update()
{

	for (int j = 0; j < _characters.size(); ++j)
	{
		// Update pociskow
		std::vector<Projectile>& temp = _characters[j].getpiFpaF();
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


			if (temp[i].getElapdedDistance() < _characters[j].getRange() / 10)
			{
				temp[i].UpdateAnimation(deltaTime);
				switch (pdir)
				{
				case Animation::Direction::UP:
				{
					temp[i]._position.setY(temp[i]._position.getY() - deltaTime * tempV);
					temp[i].setElapsedDistance(temp[i].getElapdedDistance() + deltaTime * tempV);
					break;
				}
				case Animation::Direction::DOWN:
				{
					temp[i]._position.setY(temp[i]._position.getY() + deltaTime * tempV);
					temp[i].setElapsedDistance(temp[i].getElapdedDistance() + deltaTime * tempV);
					break;
				}
				case Animation::Direction::LEFT:
				{
					temp[i]._position.setX(temp[i]._position.getX() - deltaTime * tempV);
					temp[i].setElapsedDistance(temp[i].getElapdedDistance() + deltaTime * tempV);
					break;
				}
				case Animation::Direction::RIGHT:
				{
					temp[i]._position.setX(temp[i]._position.getX() + deltaTime * tempV);
					temp[i].setElapsedDistance(temp[i].getElapdedDistance() + deltaTime * tempV);
					break;
				}

				}
				if (CheckCollisionsBullet(temp[i], j, temp[i].getX(), temp[i].getY()))
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
}

void GameEngine::ShowGUI(Vec2d position)
{
	Vec2d scale = position;
	scale._x = (0.3 + position._x - 1) / 2;
	scale._y = (0.3  + position._y - 1) / 2;
	double offsetX = 1.0;
	double offsetY = 0.3;

	// HP
	textGen->setPosition("HP", Vec2d(scale._x, scale._y));
	textGen->setPosition("HP VALUE", Vec2d(scale._x + offsetX, scale._y));
	textGen->setText("HP VALUE", std::to_string((long)_characters[0].getHealth()));
	textGen->setInfinity("HP", true);
	textGen->setInfinity("HP VALUE", true);
	// RANGE
	textGen->setPosition("RANGE", Vec2d(scale._x, scale._y + 1 * offsetY));
	textGen->setPosition("RANGE VALUE", Vec2d(scale._x + offsetX, scale._y + 1 * offsetY));
	textGen->setText("RANGE VALUE", std::to_string((long)_characters[0].getRange()));
	textGen->setInfinity("RANGE", true);
	textGen->setInfinity("RANGE VALUE", true);
	
	// SPEED
	textGen->setPosition("SPEED", Vec2d(scale._x, scale._y + 2 * offsetY));
	textGen->setPosition("SPEED VALUE", Vec2d(scale._x + offsetX, scale._y + 2 * offsetY));
	textGen->setText("SPEED VALUE", std::to_string((long)_characters[0].getMovementSpeed()));
	textGen->setInfinity("SPEED", true);
	textGen->setInfinity("SPEED VALUE", true);
	
	// ATT S
	textGen->setPosition("ATTACKS", Vec2d(scale._x, scale._y + 3 * offsetY));
	textGen->setPosition("ATTACK VALUE", Vec2d(scale._x + offsetX, scale._y + 3 * offsetY));
	textGen->setText("ATTACK VALUE", std::to_string((long)_characters[0].getAttackSpeed()));
	textGen->setInfinity("ATTACKS", true);
	textGen->setInfinity("ATTACK VALUE", true);
	
	// DMG
	textGen->setPosition("DMG", Vec2d(scale._x, scale._y + 4 * offsetY));
	textGen->setPosition("DMG VALUE", Vec2d(scale._x + offsetX, scale._y + 4 * offsetY));
	textGen->setText("DMG VALUE", std::to_string((long)_characters[0].getDamage()));
	textGen->setInfinity("DMG", true);
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

void GameEngine::HideText()
{
	//size_t size  = textGen->getAmount();
	//for (size_t i = 0; i < size; i++)
	//{
	//	textGen->
	//}
	t.Reset();
}

void GameEngine::GenNextLevel()
{
	//Generuj mape
	_map->LoadLevel(_lvlgen.generateLevel(_map, _gameDifficulty));
	//Tutaj funkcja do generowanie enemisuf
	_lvlgen.PopulateDynamics(_characters,_gameDifficulty);
	
	//Fix Player position and Camera
	_characters[0]._position._x = ceil(_map->getWidth() / 2.0) - 1;
	_characters[0]._position._y = ceil(_map->getHeight() / 2.0) - 1;
	camera.initCamera(_characters[0].getPos(), _map->getWidth(), _map->getHeight());
	
	//Delete non picked up items
	_ItemGenerator.Clear();

	//Reset all Timers
	t.Reset();
	//Reset win boolean
	lvlWin = false;
	//Close opened Doors
	Doors();

	//Debug
	debuginfo.Init(_characters);
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
		int move1;
		int move2;
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
		move1 = CheckColissions(_characters[i], i, newX, my);
		//Check in Y
		move2 = CheckColissions(_characters[i], i, mx, newY);

		//Wykonaj ruch
			if (move1==-1 && newX!=mx)
			{
				//Je¿eli w drug¹ stronie nie ma ruchu
				if (move2!=-1)
				{
					//Policz czy jest sens i dodaj do pierwotnego kierunku
					double value = mv * deltaTime;
					if (dir[0] == Animation::Direction::LEFT)
					{
						if(CheckColissions(_characters[i],i,mx-value,my)==-1) newX = mx-value;
					}
					else
					{
						if (CheckColissions(_characters[i], i, mx + value, my)==-1) newX = mx+ value;
					}
				}

				_characters[i].setX(newX);	
				if (HowMuchInY < HowMuchInX )_characters[i].updateAnimation({ Animation::Direction::NONE,(Animation::Direction)dir[0]}, deltaTime);
				_characters[i].setSide((Animation::Direction)dir[0]);
				ProcessShoot(_characters[i]);
			}
			if (move2==-1&&newY!=my)
			{
					if (move1!=-1)
					{
						
						double value = mv * deltaTime;
						if (dir[1] == Animation::Direction::UP)
						{
							if (CheckColissions(_characters[i], i, mx, my-value)==-1) newY = my-value;
						}
						else
						{
							if (CheckColissions(_characters[i], i, mx, my+value)==-1) newY = my+value;
						}
						//_characters[i].updateAnimation({ (Animation::Direction)dir[1],Animation::Direction::NONE }, deltaTime);
					}
					_characters[i].setY(newY);
					if (HowMuchInY > HowMuchInX)_characters[i].updateAnimation({ (Animation::Direction)dir[1],Animation::Direction::NONE }, deltaTime);
					_characters[i].setSide((Animation::Direction)dir[1]);
					ProcessShoot(_characters[i]);
			}

			if (move1 == 0 || move2 == 0)
			{
					if (_characters[0].isTouchable())
					{
						effectEngine.Play("hit");
						_characters[0].getHealth() -= (long)ceil(_characters[i].getDamage());
						_characters[0].Untouchable();
					}
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
		_ItemGenerator.GenerateItem((GLuint)ceil(_map->getWidth()/2.0)-1, (GLuint)ceil(_map->getHeight() / 2.0) - 1);
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

int GameEngine::CheckColissions(Character & obj, GLuint index, double x, double y)
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
		if (_map->getTile(indexes[i]).GetSolid()) return index;
	}

	//a teraz kolizje z innymi characterami
	for (GLuint j = 0; j < _characters.size(); ++j)
	{
		if (j != index) if (ShapeOverlap_DIAGS(tmp, _characters[j].getOrigin())) return j;
	}

	return -1;
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
		if (ShapeOverlap_DIAGS(tmp, _map->getTile(indexesToCheck[i]>0?(indexesToCheck[i] < (int)_map->getSize()? indexesToCheck[i]:0):0).getOrigin()))
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
		if (j != index)
		{
			if (ShapeOverlap_DIAGS(tmp, _characters[j].getOrigin()))
			{
				if (index != 0 && j == 0)
				{
					
					if (_characters[0].isTouchable())
					{
						effectEngine.Play("hit");
						//_characters[0].getHealth() -= (long)ceil(_characters[index].getDamage());
						if (_characters[0].TakeDamage(bullet))
						{
							_gameState = State::GAMEOVER;
						}
						_characters[0].Untouchable();
					}
					return true;
				}
				else if (index == 0)
				{
					effectEngine.Play("hit");
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
		}
	}

	return false;
}
