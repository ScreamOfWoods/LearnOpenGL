#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdlib.h>

const char* vertexShaderSource = 
"#version 330 core\nlayout (location = 0) in vec3 aPos;\n\nvoid main()\n{\ngl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n}";

const char* fragmentShaderSource = 
"#version 330 core\nout vec4 FragColor;\n\nvoid main()\n{\nFragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n}";

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void createBuffer(GLenum bufferType, GLsizei n, GLuint* buffer, GLsizeiptr size, GLvoid* data)
{
	glGenBuffers(n, buffer);
	glBindBuffer(bufferType, (*buffer));
	glBufferData(bufferType, size, data, GL_STATIC_DRAW);
}

GLuint createShader(GLenum shaderType, GLsizei n, const GLchar** source)
{
	GLuint shader;
	shader = glCreateShader(shaderType);

	if(!shader) {
		if(shaderType == GL_VERTEX_SHADER)
			std::cout<<"Failed to create Vertex shader\n";
		else
			std::cout<<"Failed to created Fragment shader\n";
		exit(EXIT_FAILURE);
	}
	glShaderSource(shader, n, source, NULL);
	glCompileShader(shader);
	
	int success;
	char log[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(!success) {
		glGetShaderInfoLog(shader, 512, NULL, log);
		if(shaderType == GL_VERTEX_SHADER)
			std::cout<<"Failed to compile Vertex shader\n";
		else
			std::cout<<"Failed to compile Fragment shader\n";
		
		std::cout<<log<<std::endl;
		exit(EXIT_FAILURE);
	}
	
	return shader;
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

	GLFWwindow* window = glfwCreateWindow(800, 600, "Hello GL", NULL, NULL);
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

	float vertices[] = {
		-0.5f, 0.5f, 0.0f,
		 0.25f, 0.25f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.25f, -0.25f, 0.0f
	};

	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3
	};

	GLuint VBO;
	createBuffer(GL_ARRAY_BUFFER, 1, &VBO, sizeof(vertices), (GLvoid*) vertices);

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint EBO;
	createBuffer(GL_ELEMENT_ARRAY_BUFFER, 1, &EBO, sizeof(indices), (GLvoid*) indices);

	int success;
	char log[512];

	GLuint vertexShader, fragmentShader;

	vertexShader = createShader(GL_VERTEX_SHADER, 1, &vertexShaderSource);
	fragmentShader = createShader(GL_FRAGMENT_SHADER, 1, &fragmentShaderSource);

	GLuint shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	
	if(!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, log);
		std::cout<<"Error::SHADER::PROGRAM\n"<<log<<std::endl;
	}

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*) 0);
	glEnableVertexAttribArray(0);

	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	while(!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.5f, 0.2f, 0.3f, 0.3f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glfwTerminate();

	return 0;
}
