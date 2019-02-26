//================================================================
//= Our libraries
//================================================================
#include "Maps/Map.h"
#include "Timer.h"
#include "Shader.h"


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

	//================================================================
	//= Jeden kwadrat :O
	//================================================================
	float vertices2[] = {
		// positions          // colors         coords
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,  // top left 
	};

	//================================================================
	//= Facey
	//================================================================
	unsigned int indices[] = {  // note that we start from 0!
	0, 1, 3,  // first Triangle
	1, 2, 3   // second Triangle
	};


	Shader myShader("src/vs.vs", "src/fs.fs");

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	
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

		myShader.use();
		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		/* Render here */
		//glClear(GL_COLOR_BUFFER_BIT);

		//GLLogCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
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
