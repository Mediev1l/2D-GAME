#include <GL/glew.h>
#include <GLFW/glfw3.h>

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

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(2);



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

	GLuint index[]
	{
		0, 1, 2,
		2, 3, 0
	};

	GLuint VBO;

	// Tworzymy 1 bufor
	GLLogCall(glGenBuffers(1, &VBO));

	// przypisujemy bufor jako GL_ARRAY_BUFFER (enumerator)
	GLLogCall(glBindBuffer(GL_ARRAY_BUFFER, VBO));

	// Kopiujemy zdefiniowany vertex do buforu
	GLLogCall(glBufferData(GL_ARRAY_BUFFER, 8 *  sizeof(float), vertices, GL_STATIC_DRAW));

	// okreslamy lokacje i format danych
	GLLogCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0));

	// wlaczamy attrybut 0
	GLLogCall(glEnableVertexAttribArray(0));


	GLuint IBO;
	
	// Tworzymy 1 bufor
	GLLogCall(glGenBuffers(1, &IBO));
	
	// przypisujemy bufor jako GL_ARRAY_BUFFER (enumerator)
	GLLogCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO));
	
	// Kopiujemy zdefiniowany vertex do buforu
	GLLogCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), index, GL_STATIC_DRAW));
	



	ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");

	GLuint shader = CreateShader(source.VertexShader, source.FragmentShader);


	GLLogCall(glUseProgram(shader));
	
	GLLogCall(int location = glGetUniformLocation(shader, "u_Color"));
	
	ASSERT(location != -1);


		//float time = glfwGetTime();
		//float color = (sin(time) / 2.0f) + 0.5f;


		float color = 0.0f;
		float increment = 0.005f;
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		if (color > 1.0f)
			increment = -0.05f;
		else if (color < 0.0f)
			increment = 0.05f;

		color += increment;
		

		
		GLLogCall(glUniform4f(location, color, 0.3f, 0.8f, 1.0f));


		
		GLLogCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
		
		//glDrawArrays(GL_TRIANGLES, 0, 6);


		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	glDeleteProgram(shader);

	glfwTerminate();
	return 0;
}