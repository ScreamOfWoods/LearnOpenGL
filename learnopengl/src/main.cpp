#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <glm/glm.hpp>

#include <shader.h>
#include <textures.h>
#include <transformations.h>

int width = 800;
int height = 600;
float mixValue = 0.02f;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if(glfwGetKey(window, GLFW_KEY_UP)) {
		mixValue += 0.01f;
		if(mixValue >= 1.0f) {
			mixValue = 1.0f;
		}
	}
	if(glfwGetKey(window, GLFW_KEY_DOWN)) {
		mixValue -= 0.01f;
		if(mixValue <= 0) {
			mixValue = 0.0f;
		}
	}
}

GLuint createRenderableObject(unsigned int* object, float* vertices, size_t v_size, 
		unsigned int* indices, size_t i_size, int n)
{
	GLuint vao;
	GLuint ebo;

	glGenBuffers(1, object);
	glGenBuffers(1, &ebo);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
	glBindBuffer(GL_ARRAY_BUFFER, (*object));
	glBufferData(GL_ARRAY_BUFFER, v_size, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, i_size, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, n*sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);
	//Blue Object
	if(n > 3) {
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, n*sizeof(float), (void*) (3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, n*sizeof(float), (void*) (6 * sizeof(float)));
		glEnableVertexAttribArray(2);
	}

	return vao;
}

void renderLogic(Shader* redProgram, Shader* blueProgram,
		 GLuint vaoRed, GLuint vaoBlue, GLuint texture1, GLuint texture2)
{
#if 0
	redProgram->use();
	
	float timeVal = glfwGetTime();
	float rpulse = sin(timeVal) / 2.0f + 0.5f;
	int rcolorLocation = glGetUniformLocation(redProgram->getShaderID(), "rgradient");
	
	if(rcolorLocation == -1) {
		std::cout<<"Unable to find UNIFORM variable from SHADER\n";
		exit(EXIT_FAILURE);
	}

	setClippingPlane(redProgram, 45.0f, glm::vec3(1.0f, 0.0f, 0.0f), 
			glm::vec3(0.0f, 0.0f, -3.0f), width / height, 0.01f, 100.0f);

	glUniform4f(rcolorLocation, rpulse, 0.0f, 0.0f, 1.0f);
	glBindVertexArray(vaoRed);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
#endif
	//Bind textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);

	//Use the next shader
	blueProgram->use();
	//Set uniforms
	blueProgram->setInt("textureData", 0);
	blueProgram->setInt("textureData2", 1);
	blueProgram->setFloat("mixValue", mixValue);

	setClippingPlane(blueProgram, 15.0f, glm::vec3(1.0f, 0.0f, 0.0f), 
			glm::vec3(0.0f, 0.0f, -5.0f), width / height, 0.01f, 100.0f);
	

	glBindVertexArray(vaoBlue);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

}

int main()
{
	std::cout<<"Hello GL\n";

	if(glfwInit() == GL_FALSE) {
		std::cout<<"Failed to load GLFW!\n";
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);	
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	

	GLFWwindow* window = glfwCreateWindow(width, height, "Hello GL", NULL, NULL);
	if(window == NULL) {
		std::cout<<"Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout<<"Failed to init GLAD\n";
		return -1;
	}

	//Red coordinates
	float verticesR[] = {
		 0.0f, 0.0f, 0.0f,
		 0.5f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f, -0.5f, 0.0f
	};

	//Blue coordinates
	float verticesB[] = {
		//Coordinates       //Colors	       //Textures
		-0.5f, 0.5f, 0.0f,  1.0f, 0.3f, 0.2f,  1.0f, 1.0f,
		 0.0f, 0.5f, 0.0f,  0.3f, 1.0f, 0.2f,  1.0f, 0.0f,
		 0.0f, 0.0f, 0.0f,  0.2f, 0.3f, 1.0f,  0.0f, 0.0f,
		-0.5f, 0.0f, 0.0f,  0.2f, 0.7f, 0.1f,  0.0f, 1.0f
	};

	//Indices are the same for both objects
	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3
	};

	//Create Red Object
	unsigned int redObject;
	GLuint vaoRed = createRenderableObject(&redObject, verticesR, sizeof(verticesR), indices, sizeof(indices), 3);
	//Create Blue Object
	unsigned int blueObject;
	GLuint vaoBlue = createRenderableObject(&blueObject, verticesB, sizeof(verticesB), indices, sizeof(indices), 8);
	
	//Red shader
	Shader* redShader = new Shader("redshader.vert", "redshader.fr");
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*) 0);
	glEnableVertexAttribArray(0);

	//Blue shader
	Shader* blueShader = new Shader("blueshader.vert","blueshader.fr");

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*) 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*) (3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*) (6 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//Blue texture
	unsigned int textureID1 = applyTexture("../res/container.jpg", GL_RGB);
	unsigned int textureID2 = applyTexture("../res/awesomeface.png", GL_RGBA);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	float r = 0.4f, g = 0.6f, b = 0.5f;
	bool decrease = false;

	while(!glfwWindowShouldClose(window)) {
		
		processInput(window);
		glClearColor(r, g, b, 0.3f);
		
		glClear(GL_COLOR_BUFFER_BIT);

		renderLogic(redShader, blueShader, vaoRed, vaoBlue, textureID1, textureID2);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glDeleteVertexArrays(1, &vaoRed);
	glDeleteVertexArrays(1, &vaoBlue);
	glDeleteBuffers(1, &redObject);
	glDeleteBuffers(1, &blueObject);

	glfwTerminate();

	return 0;
}
