#include "Renderer.h"



Renderer::Renderer()
	:
	_mainShader("src/Shaders/vs.vs","src/Shaders/fs.fs")
	,_maps{ "res/Sprites/Map1/map1.txt","res/Sprites/Map1/" }
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//To ma byæ wywo³ane przed u¿yciem jakiejkolwiek tekstury
	_mainShader.use();
	_mainShader.setInt("texture1", 0);
}


Renderer::~Renderer()
{
}



void Renderer::RenderMap()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (GLuint y = 0; y < (GLuint)_maps.getHeight(); y++)
	{
		for (GLuint x = 0; x < (GLuint)_maps.getWidth(); x++)
		{

			//Eksperymentalnie udowodniono ze dziala xD
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(-0.9f, 0.9f, 0.0f));
			model = glm::translate(model, glm::vec3(0.2f*x, -0.2f*y, 0.0f));


			//Skalowanko lepiej na koncu xD
			model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));


			_mainShader.setMat4("model", model);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D,_maps.getTexture(x,y));

			_mainShader.use();
			glBindVertexArray(VAO);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	}
}

void Renderer::RenderCharacter(std::vector<Character>& characters)
{
	//Rysowanie od ty³u = gracz zawsze na wierzchu
	for(int i = (int)characters.size()-1; i>-1;--i)
	{
		//Eksperymentalnie udowodniono ze dziala xD
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.9f, 0.9f, 0.0f));
		model = glm::translate(model, glm::vec3(0.2f*(characters[i].getX()), -0.2f*(characters[i].getY()), 0.0f));


		//Skalowanko lepiej na koncu xD
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f));


		_mainShader.setMat4("model", model);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, characters[i].getTexture());

		_mainShader.use();
		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

}

void Renderer::RenderItems(std::vector<Item>& items)
{
	//Od ty³u bo sobie skopiowa³em z characters kappa
	for (int i = (int)items.size()-1; i > -1; --i)
	{
		if (items[i].getOnMap() == true)
		{
			//Eksperymentalnie udowodniono ze dziala xD
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(-0.9f, 0.9f, 0.0f));
			model = glm::translate(model, glm::vec3(0.2f*(items[i].getX()), -0.2f*(items[i].getY()), 0.0f));


			//Skalowanko lepiej na koncu xD
			model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f));


			_mainShader.setMat4("model", model);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, items[i].getTexture());

			_mainShader.use();
			glBindVertexArray(VAO);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	}
}
