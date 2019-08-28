#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdlib.h>

const char* vertexShaderSource = 
"#version 330 core\nlayout (location = 0) in vec3 aPos;\n\nvoid main()\n{\ngl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n}";

const char* fragmentShaderSourceR = 
"#version 330 core\nout vec4 FragColor;\n\nvoid main()\n{\nFragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n}";

const char* fragmentShaderSourceB = 
"#version 330 core\nout vec4 FragColor;\n\nvoid main()\n{\nFragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);\n}";

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

GLuint createRenderableObject(unsigned int* object, float* vertices, size_t v_size, 
		unsigned int* indices, size_t i_size)
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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0);

	return vao;
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

int createShaderProgram(GLuint vertexShader, GLuint fragmentShader)
{
	GLuint program;
	program = glCreateProgram();
	if(!program) {
		std::cout<<"Failed to create shader program\n";
		exit(EXIT_FAILURE);
	}

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);
	
	int success;
	char log[512];

	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if(!success) {
		std::cout<<"Failed to link shader program\n";
		exit(EXIT_FAILURE);
	}

	return program;
}

void renderLogic(GLuint redProgram, GLuint blueProgram,
		 GLuint vaoRed, GLuint vaoBlue)
{
	glUseProgram(redProgram);
	glBindVertexArray(vaoRed);
	
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glUseProgram(blueProgram);
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

	//Red coordinates
	float verticesR[] = {
		-0.5f, 0.5f, 0.0f,
		 0.0f, 0.5f, 0.0f,
		 0.0f, 0.0f, 0.0f,
		-0.5f, 0.0f, 0.0f
	};

	//Blue coordinates
	float verticesB[] = {
		 0.0f, 0.0f, 0.0f,
		 0.5f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f, -0.5f, 0.0f
	};

	//Indices are the same for both objects
	unsigned int indices[] = {
		0, 1, 2,
		0, 2, 3
	};

	//Create Red Object
	unsigned int redObject;
	GLuint vaoRed = createRenderableObject(&redObject, verticesR, sizeof(verticesR), indices, sizeof(indices));
	//Create Blue Object
	unsigned int blueObject;
	GLuint vaoBlue = createRenderableObject(&redObject, verticesB, sizeof(verticesB), indices, sizeof(indices));

	//Create Red Shader
	GLuint vertexShader, fragmentShaderR;

	vertexShader = createShader(GL_VERTEX_SHADER, 1, &vertexShaderSource);
	fragmentShaderR = createShader(GL_FRAGMENT_SHADER, 1, &fragmentShaderSourceR);

	GLuint shaderProgramR;
	shaderProgramR = createShaderProgram(vertexShader, fragmentShaderR);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*) 0);
	glEnableVertexAttribArray(0);

	//Create Blue Shader
	GLuint fragmentShaderB;

	fragmentShaderB = createShader(GL_FRAGMENT_SHADER, 1, &fragmentShaderSourceB);

	GLuint shaderProgramB;
	shaderProgramB = createShaderProgram(vertexShader, fragmentShaderB);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*) 0);
	glEnableVertexAttribArray(0);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShaderR);
	glDeleteShader(fragmentShaderB);

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	while(!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.0f, 1.0f, 0.0f, 0.3f);
		glClear(GL_COLOR_BUFFER_BIT);

		renderLogic(shaderProgramR, shaderProgramB, vaoRed, vaoBlue);
		
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
