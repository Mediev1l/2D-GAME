#include "Renderer.h"



Renderer::Renderer()
	:
	_mainShader("src/Shaders/vs.vs","src/Shaders/fs.fs")
	,_maps{ "res/Sprites/Map1/map1.txt","" }
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
}


Renderer::~Renderer()
{
}

void Renderer::Render(std::vector<Character>& _characters)
{
	//Powiedzmy ze mapa bedzie 10/10 kafeletk

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_mainShader.use();
	_mainShader.setInt("texture1", 0);

	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{

			//Eksperymentalnie udowodniono ze dziala xD
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(-0.9f, 0.9f, 0.0f));
			model = glm::translate(model, glm::vec3(0.2f*x,-0.2f*y,0.0f));
			

			//Skalowanko lepiej na koncu xD
			model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
			

			_mainShader.setMat4("model", model);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, _maps.getTextureID(y*10+x));

			_mainShader.use();
			glBindVertexArray(VAO);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	}

	//Drawing the player
	{
		//Eksperymentalnie udowodniono ze dziala xD
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.9f, 0.9f, 0.0f));
		model = glm::translate(model, glm::vec3(0.2f*(_characters[0].getX()), -0.2f*(_characters[0].getY()), 0.0f));


		//Skalowanko lepiej na koncu xD
		model = glm::scale(model, glm::vec3(0.08f, 0.08f, 0.08f));


		_mainShader.setMat4("model", model);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _characters[0].getTexture());

		_mainShader.use();
		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

}
