//================================================================
//= Our libraries
//================================================================
#define STB_IMAGE_IMPLEMENTATION
#include "Maps/Map.h"
#include "Timer.h"
#include "Renderer/Renderer.h"


//================================================================
//= Windows Libraries
//================================================================
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>





//================================================================
//= Tak
//================================================================
#define ASSERT(x) if(!(x)) __debugbreak();
#define GLLogCall(x) GLClearError(); x; ASSERT(GLCheckError(#x, __FILE__, __LINE__))

static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}


//================================================================
//= Window Events Callbacks
//================================================================
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);




//================================================================
//= GLOBALSETTINGS
//================================================================
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;


Timer t;
int main(void)
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
	GLFWwindow* window;
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
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


	std::cout << glGetString(GL_VERSION) <<std::endl;
	Renderer renderer;
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{

		//Providing delta Time
		t.Mark();
		float deltaTime = t.getDelta();
		while (deltaTime <= t.getSingleFrameTime())
		{
			t.Mark();
			deltaTime += t.getDelta();
		}
		t.setGlobalDelta(deltaTime);
		//Updating Label name
		char buffer[20];
		_itoa_s((1 / deltaTime), buffer, 10);
		std::string a = "Kacp3r3 & Bartek Playground FPS: ";
		a += buffer;
		glfwSetWindowTitle(window, a.c_str());


		// input
		// -----
		processInput(window);

		renderer.Render();


		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	}
	catch (std::runtime_error &e)
	{
		std::cout << e.what();
		int a;
		std::cin >> a;
	}
	return 0;
}


void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	float deltaTime = t.getGlobalDelta();


	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{ }
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
	}
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	//camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	//camera.ProcessMouseScroll(yoffset);
}
