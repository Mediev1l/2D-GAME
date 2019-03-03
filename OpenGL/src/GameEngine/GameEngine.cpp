#include "GameEngine.h"

GameEngine::GameEngine()
	:
	window(nullptr)
	, renderer(nullptr)
	, t()
	, SCR_WIDTH(800)
	, SCR_HEIGHT(800)
	, lastX(SCR_WIDTH / 2.0)
	, lastY(SCR_HEIGHT / 2.0)
	, firstMouse(true)
	, WindowName("Kacp3r3 & Bartek Playground")
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


		//================================================================
		//= Creating the Window
		//================================================================
		window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello World", NULL, NULL);
		if (!window)
		{
			glfwTerminate();
			//return -1; void nie zwraca
		}

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

		renderer = new Renderer();
		_map = &renderer->getMap();
	}
	catch (std::runtime_error &e)
	{
		std::cout << e.what();
		int a;
		std::cin >> a;
	}

	//PLAYER ADDED HERE
	_characters.push_back(Hero(5.0, 6.0, 3.0, "res/Sprites/Player/issac.png"));

	//ITEMS Na razie jeden na sztywno || pozniej vektor wczytanych itemow z pliku
	//Na sztywno ustawianie na mapie ze jest tam item
	_items.emplace_back("res/Sprites/Items/", "res/Items/", 0);
	_items[0].setX(5);
	_items[0].setY(7);
	_map->setTileContent(5, 7, Tile::Content::Item);

}

void GameEngine::Game_Run()
{

	// Game  Initialization
	Game_Init();

	


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{

		//Providing delta Time
		t.Mark();
		while (t.getDelta() <= t.getSingleFrameTime())
		{
			t.Mark();
		}
		//Updating Label name
		std::string a = WindowName + " FPS: " + std::to_string((int)round(1 / t.getDelta()));
		glfwSetWindowTitle(window, a.c_str());


		// input
		// -----
		processInput();


		//Renderowanie || rozdzielone by gracz byl rysowany na koncu
		renderer->RenderMap();
		renderer->RenderItems(_items);
		renderer->RenderCharacter(_characters);


		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
}


void GameEngine::processInput()
{
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
	{
		std::cout << "PlayerX: " << _characters[0].getX() << '\n';
		std::cout << "PlayerY: " << _characters[0].getY() << '\n';
		std::cout << "PlayerVelocity: " << _characters[0].getVelocity() << '\n';
		std::cout << "boots: " << _items[0].getMovementSpeed() << '\n';
	}
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		if (_canPickup)
		{
			ProcessItemPickup();
		}
	}

	float deltaTime = t.getDelta();
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS
		||
		glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		ProcessPlayerMove(deltaTime, Direction::UP);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS
		||
		glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		ProcessPlayerMove(deltaTime, Direction::DOWN);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS
		||
		glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		ProcessPlayerMove(deltaTime, Direction::LEFT);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS
		||
		glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		ProcessPlayerMove(deltaTime, Direction::RIGHT);
	}
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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

void GameEngine::ProcessPlayerMove(double deltaTime, Direction dir)
{
	//Zmienne upraszczaj¹ce kod
	double px = _characters[0].getX();
	double py = _characters[0].getY();
	double pv = _characters[0].getVelocity();
	double newX = px;
	double newY = py;

	//Ustaw flage na 0
	_canPickup = false;

	switch (dir)
	{
		case UP:
		{
			newY -= deltaTime * pv;
			break;
		}
		case DOWN:
		{
			newY += deltaTime * pv;
			break;
		}
		case LEFT:
		{
			newX -= deltaTime * pv;
			break;
		}
		case RIGHT:
		{
			newX += deltaTime * pv;
			break;
		}
	}

	GLuint fixedX;
	GLuint fixedY;
	//Sprawdz czy pod now¹ pozycj¹ jest kolizja
	bool collision = CheckForPlayerColissionX(newX,dir,fixedX,fixedY) || CheckForPlayerColissionY(newY,dir, fixedX, fixedY);
	if (collision)
	{
		std::cout << "Kolizja!" << '\n';
		switch (_map->getTileContent(fixedX, fixedY))
		{
			//Nigdy sie nie wydarzy ale co tam
			case Tile::Content::Nothing:
			{
				break;
			}
			case Tile::Content::Obstacle:
			{
				//Tutaj return
				return;
				break;
			}
			case Tile::Content::Item:
			{
				//Tutaj proces przechwycenia itemka
				_canPickup = true;
				break;
			}
		}
	}
	_characters[0].setX(newX);
	_characters[0].setY(newY);
}

bool GameEngine::CheckForPlayerColissionX(double newX, Direction dir, GLuint& fx, GLuint& fy)
{
	bool left = dir == LEFT ? true : false;
	//Sprawdz czy pod tym X jest obstacle
	if (dir == LEFT || dir == RIGHT)
	{
			if (left)
			{
				//Ide w lewo i nachodze na klocek od spodu
				//  G³az y: 2
				//  Gracz y: 2.xyz
				if (_map->isObstacle((GLuint)(newX + 0.1f), (GLuint)(_characters[0].getY() + 0.1f)))
				{
					fx = (GLuint)(newX + 0.1f);
					fy = (GLuint)(_characters[0].getY() + 0.1f);
					return true;
				}	
				//Ide w lewo i nachodze klocek od góry
				// Gracz 1.89
				// G³az 2
				else if (_map->isObstacle((GLuint)(newX + 0.1), (GLuint)round(_characters[0].getY())))
				{
					fx = (GLuint)(newX + 0.1f);
					fy = (GLuint)round(_characters[0].getY());
					return true;
				}	
				//Jakis trzeci Przypadek lol
				else if (_map->isObstacle((GLuint)(newX + 0.1f), (GLuint)ceil(_characters[0].getY() - 0.1f)))
				{
					fx = (GLuint)(newX + 0.1f);
					fy = (GLuint)ceil(_characters[0].getY() - 0.1f);
					return true;
				}
			}
			else
			{

				if (_map->isObstacle((GLuint)(newX + 0.9f), GLuint(_characters[0].getY() + 0.1f)))
				{
					fx = (GLuint)(newX + 0.9f);
					fy = GLuint(_characters[0].getY() + 0.1f);
					return true;
				}
				else if (_map->isObstacle((GLuint)(newX + 0.9f), (GLuint)round(_characters[0].getY())))
				{
					fx = (GLuint)(newX + 0.9f);
					fy = (GLuint)round(_characters[0].getY());
					return true;
				}
				else if (_map->isObstacle((GLuint)(newX + 0.9f), (GLuint)ceil(_characters[0].getY() - 0.1f)))
				{
					fx = (GLuint)(newX + 0.9f);
					fy = (GLuint)ceil(_characters[0].getY() - 0.1f);
					return true;
				}
			}
			return false;
		}
		 return false;
}

bool GameEngine::CheckForPlayerColissionY(double newY, Direction dir, GLuint& fx, GLuint& fy)
{
	bool top = dir == UP ? true : false;

	if (dir == UP || dir == DOWN)
	{
		//Sprawdz czy pod tym Y jest obstacle
		if (top)
		{
			if (_map->isObstacle(int(_characters[0].getX() + 0.1f), (GLuint)(newY + 0.1f))  )
			{
				fx = GLuint(_characters[0].getX() + 0.1f);
				fy = (GLuint)(newY + 0.1f);
				return true;
			}
			else if (_map->isObstacle((GLuint)round(_characters[0].getX()), (GLuint)(newY + 0.1f)))
			{
				fx = (GLuint)round(_characters[0].getX());
				fy = (GLuint)(newY + 0.1f);
				return true;
			}
			else if (_map->isObstacle((GLuint)ceil(_characters[0].getX() - 0.1f), (GLuint)(newY + 0.1f)))
			{
				fx = (GLuint)ceil(_characters[0].getX() - 0.1f);
				fy = (GLuint)(newY + 0.1f);
				return true;
			}
		}
		else
		{
			if (_map->isObstacle(GLuint(_characters[0].getX() + 0.1f), (GLuint)(newY + 0.9f)) )
			{
				fx = GLuint(_characters[0].getX() + 0.1f);
				fy = (GLuint)(newY + 0.9f);
				return true;
			}
			else if (_map->isObstacle((GLuint)round(_characters[0].getX()), (GLuint)(newY + 0.9f)) )
			{
				fx = (GLuint)round(_characters[0].getX());
				fy = (GLuint)(newY + 0.9f);
				return true;
			}
			else if (_map->isObstacle((GLuint)ceil(_characters[0].getX() - 0.1f), (GLuint)(newY + 0.9f)) )
			{
				fx = (GLuint)ceil(_characters[0].getX() - 0.1f);
				fy = (GLuint)(newY + 0.9f);
				return true;
			}
		}
		return false;
	}
	return false;
}

void GameEngine::ProcessItemPickup()
{
	double px = _characters[0].getX();
	double py = _characters[0].getY();

	GLuint nearestid=-1;
	double distance=100.0;
	for (GLuint i = 0; i < _items.size(); ++i)
	{
		if (_items[i].getOnMap())
		{
			double localdist = abs(_items[i].getX() - px) + abs(_items[i].getY() - py);
			if (localdist < distance)
			{
				distance = localdist;
				nearestid = i;
			}
		}
	}
	
	if (nearestid != -1)
	{
		_characters[0].consumeItem(_items[nearestid]);
		_items[nearestid].setOnMap(false);
		_map->setTileContent((GLuint)_items[nearestid].getX(), (GLuint)_items[nearestid].getY(), Tile::Content::Nothing);
	}
}
