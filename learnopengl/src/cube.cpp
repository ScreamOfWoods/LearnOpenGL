#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <stdlib.h>
#include <math.h>

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

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float deltaTime = 0.0f;
float lastFrame = 0.0f;

void processInput(GLFWwindow* window)
{

	float cameraSpeed = 2.5f * deltaTime;
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cameraPos += cameraSpeed * cameraFront;
	}
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cameraPos -= cameraSpeed * cameraFront;
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

	glm::vec3 cubePositions[] = {
		glm::vec3( 0.0f,  0.0f,  0.0f), 
		glm::vec3( 2.0f,  5.0f, -15.0f), 
		glm::vec3(-1.5f, -2.2f, -2.5f),  
		glm::vec3(-3.8f, -2.0f, -12.3f),  
		glm::vec3( 2.4f, -0.4f, -3.5f),  
		glm::vec3(-1.7f,  3.0f, -7.5f),  
		glm::vec3( 1.3f, -2.0f, -2.5f),  
		glm::vec3( 1.5f,  2.0f, -2.5f), 
		glm::vec3( 1.5f,  0.2f, -1.5f), 
		glm::vec3(-1.3f,  1.0f, -1.5f)  
	};


	VertexArray cubeVAO;
	VertexLayout cubeLayout;
	cubeLayout.push(3);
	cubeLayout.push(3);
	VertexBuffer cubeVBO(verticesCube, sizeof(verticesCube));
	cubeVAO.addBuffer(cubeVBO, cubeLayout);
	ElementBuffer cubeEBO(indicesCube, sizeof(indicesCube));
	
	Shader* cubeShader = new Shader("cube.vert", "cube.fr");
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

	while(!glfwWindowShouldClose(window)) {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		glClearColor(0.2f, 0.3f, 0.2f, 0.1f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#if 0
		va.bind();
		redShader->use();
		float timeVal = glfwGetTime();
		float rpulse = sin(timeVal) / 2.0f + 0.5f;
		int rcolorLocation = glGetUniformLocation(redShader->getShaderID(), "rgradient");
		
		if(rcolorLocation == -1) {
			std::cout<<"Unable to find UNIFORM variable from SHADER\n";
			exit(EXIT_FAILURE);
		}
		setClippingPlane(redShader, 45.0f, glm::vec3(0.5f, 1.0f, 0.0f), -55.0f * (float)glfwGetTime(),
			glm::vec3(0.0f, 0.0f, -3.0f), (float) width / (float) height, 0.1f, 100.0f);

		glUniform4f(rcolorLocation, rpulse, 0.0f, 0.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		
		glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		glm::mat4 projection = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		cubeShader->setMatrix("projection", projection);
		cubeShader->setMatrix("view", view);
		
		//Camera setup
		//Z axis
		glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
		//X axis
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
		//Y axis
		glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
#endif

		cubeShader->use();

		float radius = 10.0f;
		float camX = sin(glfwGetTime()) * radius;
		float camZ = cos(glfwGetTime()) * radius;
		glm::mat4 cameraView = glm::mat4(1.0f);
		cameraView = glm::lookAt(
			cameraPos, cameraPos + cameraFront, cameraUp
		);
		cubeShader->setMatrix("view", cameraView);
		cubeShader->setMatrix("projection", projection);
		cubeVAO.bind();
		for(int i = 0; i < 10; i++) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * (i + 1) * glfwGetTime();
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			cubeShader->setMatrix("model", model);

			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		}
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glfwTerminate();

	return 0;
}
