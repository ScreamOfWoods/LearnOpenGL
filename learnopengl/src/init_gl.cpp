#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdlib.h>

#include <init_gl.h>

GLFWwindow* createWindow(int major, int minor, std::string hint, int width, int height)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, hint.c_str(), NULL, NULL);
	return window;
	
}

GLFWwindow* initWorkspace(int majorVersion, int minorVersion, std::string hint, int width,int height)
{
	if(glfwInit() == GL_FALSE) {
		std::cerr<<"Failed to init GLFW!\n";
		exit(EXIT_FAILURE);
	}
	
	GLFWwindow* window;
	window = createWindow(majorVersion, minorVersion, hint, width, height);
	if(window == NULL) {
		std::cerr<<"Failed to create GLFW window!\n";
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
		std::cerr<<"Failed to init GLAD!\n";
		exit(EXIT_FAILURE);
	}

	glEnable(GL_DEPTH_TEST);

	return window;
}
