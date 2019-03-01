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
	}
	catch (std::runtime_error &e)
	{
		std::cout << e.what();
		int a;
		std::cin >> a;
	}

	//PLAYER ADDED HERE
	_characters.push_back(Hero(5, 5, 3, "res/Sprites/Player/issac.png"));

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
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	float deltaTime = t.getDelta();
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		_characters[0].UpdateY(-_characters[0].getVelocity()*deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		_characters[0].UpdateY(_characters[0].getVelocity()*deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		_characters[0].UpdateX(-_characters[0].getVelocity()*deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		_characters[0].UpdateX(_characters[0].getVelocity()*deltaTime);
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
