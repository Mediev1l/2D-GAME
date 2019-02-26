#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Timer.h"
#include "Shader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLLogCall(x) GLClearError(); x; ASSERT(GLCheckError(#x, __FILE__, __LINE__))

static void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

static bool GLCheckError(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cerr << "[OpenGL Error] (" << error << ")" << std::endl;
		std::cerr << "[Function] " << function << "" << std::endl;
		std::cerr << "[File] " << file << "" << std::endl;
		std::cerr << "[Line] (" << line << ")" << std::endl;
		return false;
	}

	return true;
}

struct ShaderProgramSource
{
	std::string VertexShader;
	std::string FragmentShader;
};

ShaderProgramSource ParseShader(const std::string& filePath)
{
	std::ifstream stream(filePath);

	std::stringstream ss[2];

	enum class type
	{
		DEFAULT = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};

	std::string line;
	type typ = type::DEFAULT;
	while (std::getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				typ = type::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				typ = type::FRAGMENT;
		}
		else
		{
			ss[(int)typ] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}

static GLuint CompileShader(GLuint type,const std::string& source)
{
	GLuint id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, NULL);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{

		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));

		glGetShaderInfoLog(id, sizeof(int), &length, message);
		std::cerr << "Error durning compiling " << (type == GL_VERTEX_SHADER ? "Vertex Shader" : "Fragment Shader")<<std::endl;
		std::cerr << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

// funkcja do przetworzenia shaderow
static int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	// utworzenie programu zawierajacego zawartosc polaczonych shaderow
	GLuint program = glCreateProgram();
	GLLogCall(GLuint vs = CompileShader(GL_VERTEX_SHADER, vertexShader));
	GLLogCall(GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader));
	
	// dodanie shaderow do programu
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;

}

void processInput(GLFWwindow *window);

Timer t;
int main(void)
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window;

	/* Initialize the library */

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	//glfwSwapInterval(2);



	if (glewInit() != GLEW_OK)
		std::cout << "ERROR";


	std::cout << glGetString(GL_VERSION) <<std::endl;

	float vertices[] = 
	{
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.5f,  0.5f,
		-0.5f,  0.5f
	};

	float vertices2[] = {
		// positions          // colors         coords
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,  // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,  // top left 
	};

	Shader myShader("src/vs.vs", "src/fs.fs");

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	

		//float time = glfwGetTime();
		//float color = (sin(time) / 2.0f) + 0.5f;


		float color = 0.0f;
		float increment = 0.005f;
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

		if (color > 1.0f)
			increment = -0.05f;
		else if (color < 0.0f)
			increment = 0.05f;

		color += increment;

		//GLLogCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
		
		glDrawArrays(GL_TRIANGLES, 0, 4);


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
		std::cout << "Klikam cos?";
		//camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		//camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		//camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		//camera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}