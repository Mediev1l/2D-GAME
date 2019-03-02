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
	_characters.push_back(Hero(5.0f, 6.0f, 3.0f, "res/Sprites/Player/issac.png"));

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


		//Renderowanie
		renderer->Render(_characters);


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
	}
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	//Ja to napisze ³adniej ale póŸniej Ok? XD
	float deltaTime = t.getDelta();
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		CheckForPlayerColissionY(deltaTime, true);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		CheckForPlayerColissionY(deltaTime, false);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		CheckForPlayerColissionX(deltaTime, true);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		CheckForPlayerColissionX(deltaTime, false);
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

void GameEngine::CheckForPlayerColissionX(float deltaTime, bool left)
{
	//Przesuniêcie
	float newX = _characters[0].getVelocity()*deltaTime;

	//Domniemana nowa pozycja
	float newXTest = _characters[0].getX()+(left?-newX:newX);

	//Sprawdz czy pod tym X jest obstacle
	if ( 
		left?
		//Ide w lewo i nachodze na klocek od spodu
		//  G³az y: 2
		//  Gracz y: 2.xyz
		_map->isObstacle((int)(newXTest+0.1f), int(_characters[0].getY()+0.1f ))
		||
		//Ide w lewo i nachodze klocek od góry
		// Gracz 1.89
		// G³az 2
		_map->isObstacle((int)(newXTest + 0.1f), round(_characters[0].getY()))
		||
		//Jakis trzeci Przypadek lol
		_map->isObstacle((int)(newXTest + 0.1f), ceil(_characters[0].getY()-0.1f))
		
		:

		_map->isObstacle((int)(newXTest+0.9f), int(_characters[0].getY()+0.1f ))
		||
		_map->isObstacle((int)(newXTest + 0.9f), round(_characters[0].getY() ))
		||
		_map->isObstacle((int)(newXTest + 0.9f), ceil(_characters[0].getY()-0.1f ))
		)
	{
		std::cout << "Kolizja!" << std::endl;
		//_characters[0].setX(left?(int)newXTest + 1.0f:(int)newXTest-1.0f);
	}
	else _characters[0].UpdateX(left?-newX:newX);
}

void GameEngine::CheckForPlayerColissionY(float deltaTime, bool top)
{
	//Przesuniêcie
	float newY = _characters[0].getVelocity()*deltaTime;

	//Domniemana nowa pozycja
	float newYTest = _characters[0].getY() + (top ? -newY : newY);

	//Sprawdz czy pod tym Y jest obstacle
	if (
		top ?
		_map->isObstacle( int(_characters[0].getX()+0.1f), (int)(newYTest + 0.1f))
		||
		_map->isObstacle(round(_characters[0].getX()), (int)(newYTest + 0.1f))
		||
		_map->isObstacle(ceil(_characters[0].getX() - 0.1f), (int)(newYTest + 0.1f))
		:
		_map->isObstacle(int(_characters[0].getX()+0.1f), (int)(newYTest + 0.9f))
		||
		_map->isObstacle( round(_characters[0].getX()), (int)(newYTest + 0.9f))
		||
		_map->isObstacle(ceil(_characters[0].getX()-0.1f), (int)(newYTest + 0.9f))
		)

	{
		std::cout << "Kolizja!" << std::endl;
		//_characters[0].setY(top?(int)newYTest + 1.0f:(int)newYTest-1.0f);
	}
	else _characters[0].UpdateY(top ? -newY : newY);
}
