#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdlib.h>
#include <math.h>

const char* vertexShaderSourceR = 
"#version 330 core\nlayout (location = 0) in vec3 aPos;\n\nvoid main()\n{\ngl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n}";

const char* vertexShaderSourceB = 
"#version 330 core\nlayout (location = 0) in vec3 aPos;\nlayout (location = 1) in vec3 color;\nout vec3 vColor;\nvoid main()\n{\ngl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\nvColor = color;\n}";

const char* fragmentShaderSourceR = 
"#version 330 core\nout vec4 FragColor;\nuniform vec4 rgradient;\nvoid main()\n{\nFragColor = rgradient;\n}";

const char* fragmentShaderSourceB = 
"#version 330 core\nout vec4 FragColor;\nin vec3 vColor;\nvoid main()\n{\nFragColor = vec4(vColor, 1.0f);\n}";

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
	}

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
		glGetProgramInfoLog(program, 512, NULL, log);
		std::cout<<log<<std::endl;
		exit(EXIT_FAILURE);
	}

	return program;
}

void renderLogic(GLuint redProgram, GLuint blueProgram,
		 GLuint vaoRed, GLuint vaoBlue)
{
	glUseProgram(redProgram);
	
	float timeVal = glfwGetTime();
	float rpulse = sin(timeVal) / 2.0f + 0.5f;
	int rcolorLocation = glGetUniformLocation(redProgram, "rgradient");
	
	if(rcolorLocation == -1) {
		std::cout<<"Unable to find UNIFORM variable from SHADER\n";
		exit(EXIT_FAILURE);
	}

	glUniform4f(rcolorLocation, rpulse, 0.0f, 0.0f, 1.0f);
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
		 0.0f, 0.0f, 0.0f,
		 0.5f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f, -0.5f, 0.0f
	};

	//Blue coordinates
	float verticesB[] = {
		//Coordinates       //Colors
		-0.5f, 0.5f, 0.0f,  1.0f, 0.3f, 0.2f,
		 0.0f, 0.5f, 0.0f,  0.3f, 1.0f, 0.2f,
		 0.0f, 0.0f, 0.0f,  0.2f, 0.3f, 1.0f,
		-0.5f, 0.0f, 0.0f,  0.2f, 0.7f, 0.1f
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
	GLuint vaoBlue = createRenderableObject(&redObject, verticesB, sizeof(verticesB), indices, sizeof(indices), 6);

	//Create Red Shader
	GLuint vertexShaderR, fragmentShaderR;

	vertexShaderR = createShader(GL_VERTEX_SHADER, 1, &vertexShaderSourceR);
	fragmentShaderR = createShader(GL_FRAGMENT_SHADER, 1, &fragmentShaderSourceR);

	GLuint shaderProgramR;
	shaderProgramR = createShaderProgram(vertexShaderR, fragmentShaderR);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*) 0);
	glEnableVertexAttribArray(0);

	//Create Blue Shader
	GLuint vertexShaderB, fragmentShaderB;

	vertexShaderB = createShader(GL_VERTEX_SHADER, 1, &vertexShaderSourceB);
	fragmentShaderB = createShader(GL_FRAGMENT_SHADER, 1, &fragmentShaderSourceB);

	GLuint shaderProgramB;
	shaderProgramB = createShaderProgram(vertexShaderB, fragmentShaderB);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*) 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*) (3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glDeleteShader(vertexShaderR);
	glDeleteShader(vertexShaderB);
	glDeleteShader(fragmentShaderR);
	glDeleteShader(fragmentShaderB);

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	float r = 0.4f, g = 0.6f, b = 0.5f;
	bool decrease = false;

	while(!glfwWindowShouldClose(window)) {
		
		processInput(window);
		glClearColor(r, g, b, 0.3f);
		
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
