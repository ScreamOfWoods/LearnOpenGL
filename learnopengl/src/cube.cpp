#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdlib.h>

#include <shader.h>
#include <transformations.h>
#include <textures.h>
#include <init_gl.h>

const int maj = 3;
const int min = 3;
const int width = 800;
const int height =  600;

int main()
{
	initWorkspace(maj, min, "Cube", width, height);

	float cubeVertices[] = {
		//front vertices
		//coordinates		//textures
		-0.5f, 0.5f, 0.5f,	0.0f, 1.0f,
		0.5f, 0.5f, 0.5f,	1.0f, 1.0f,
		0.5f, -0.5f, 0.5f,	1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f,	0.0f, 0.0f,
		//back vertices
		//coordinates		//textures
		-0.5f, 0.5f, -0.5f,	0.0f, 1.0f,
		0.5f, 0.5f, -0.5f,	1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,	1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f
	};

	unsigned int cubeIndices[] = {
		//Front
		0, 3, 2, 0, 1, 2,
		//Back
		4, 7, 6, 4, 5, 6,
		//Top
		4, 0, 1, 4, 5, 1,
		//Bottom
		7, 3, 2, 7, 6, 2,
		//Left
		0, 4, 3, 4, 3, 7,
		//Right
		5, 1, 2, 5, 6, 2
	};

	unsigned int cubeBuffers[2];
	unsigned int cubeVao;

	//Vertex Buffer Objects
	//0 - Array buffer, 1 - Element buffer
	glGenBuffers(2, cubeBuffers);
	//Fit the vertices data
	glBindBuffer(GL_ARRAY_BUFFER, cubeBuffers[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
	//Fit the indices data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeBuffers[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

	//Generate Vertex Array Object
	glGenVertexArrays(1, &cubeVao);
	glBindVertexArray(cubeVao);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Add a fancy texture
	applyTexture("../res/container.jpg", GL_RGB);

	return 0;
}
