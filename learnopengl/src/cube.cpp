#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <stdlib.h>

#include <shader.h>
#include <transformations.h>
#include <textures.h>
#include <init_gl.h>
#include <vertexBuffer.h>
#include <elementBuffer.h>
#include <vertexArray.h>
#include <vertexLayout.h>

const int maj = 3;
const int min = 3;
const int width = 800;
const int height =  600;

void processInput(GLFWwindow* window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void framebufferSizeCallback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);
}

int main()
{
	GLFWwindow* window = initWorkspace(maj, min, "Cube", width, height);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	float verticesR[] = {
		 0.0f, 0.0f, 0.0f,
		 0.5f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f, -0.5f, 0.0f
	};

	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3
	};

	VertexArray va;
	VertexLayout layout;
	VertexBuffer vb(verticesR, sizeof(verticesR));
	layout.push(3);
	va.addBuffer(vb, layout);
	ElementBuffer eb(indices, sizeof(indices));


	Shader* redShader = new Shader("redshader.vert", "redshader.fr");

	float verticesCube[] = {
		//Coordinates Front	//Colours
		-0.5f, 0.5f, 0.5f,	1.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f,	0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f,	0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f,	1.0f, 1.0f, 0.1f,
		//Coordinates Back	//Colours
		-0.5f, 0.5f, -0.5f,	1.0f, 0.0f, 0.0f,
		0.5f, 0.5f, -0.5f,      0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, -0.5f,     0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 0.1f
	};

	unsigned int indicesCube[] = {
		//Front
		0, 3, 2, 0, 2, 1,	
		//Back
		4, 7, 6, 4, 6, 5,
		//Top
		4, 0, 1, 4, 1, 5,
		//Bottom
		7, 3, 2, 7, 2, 6,
		//Left
		4, 0, 3, 4, 3, 7,
		//Right
		5, 1, 2, 5, 2, 6
	};

	VertexArray cubeVAO;
	VertexLayout cubeLayout;
	cubeLayout.push(3);
	cubeLayout.push(3);
	VertexBuffer cubeVBO(verticesCube, sizeof(verticesCube));
	cubeVAO.addBuffer(cubeVBO, cubeLayout);
	ElementBuffer cubeEBO(indicesCube, sizeof(indicesCube));
	
	Shader* cubeShader = new Shader("cube.vert", "cube.fr");

	while(!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.2f, 0.1f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		va.bind();
		redShader->use();
		float timeVal = glfwGetTime();
		float rpulse = sin(timeVal) / 2.0f + 0.5f;
		int rcolorLocation = glGetUniformLocation(redShader->getShaderID(), "rgradient");
		
		if(rcolorLocation == -1) {
			std::cout<<"Unable to find UNIFORM variable from SHADER\n";
			exit(EXIT_FAILURE);
		}
		setClippingPlane(redShader, 45.0f, glm::vec3(1.0f, 0.0f, 0.0f), -55.0f,
			glm::vec3(0.0f, 0.0f, -3.0f), (float) width / (float) height, 0.1f, 100.0f);

		glUniform4f(rcolorLocation, rpulse, 0.0f, 0.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		cubeShader->use();
		setClippingPlane(cubeShader, 35.0f, glm::vec3(1.0f, 0.0f, 0.0f), -55.0f,
			glm::vec3(0.0f, 0.0f, -7.0f), (float) width / (float) height, 0.1f, 100.0f);

		cubeVAO.bind();
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}
