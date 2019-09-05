#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdlib.h>

#include <shader.h>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);	
	fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);	

	try {
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch(std::ifstream::failure e) {
		std::cout<<"Failed to load Shader source files\n";
		exit(EXIT_FAILURE);
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	unsigned int vertex, fragment;
	int success;
	char log[512];

	vertex = createShader(GL_VERTEX_SHADER, 1, &vShaderCode);
	fragment = createShader(GL_FRAGMENT_SHADER, 1, &fShaderCode);
	
	shaderID = createShaderProgram(vertex, fragment);
}

Shader::~Shader()
{
	glDeleteProgram(shaderID);
}

GLuint Shader::createShader(GLenum shaderType, GLsizei n, const GLchar** source)
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

int Shader::createShaderProgram(GLuint vertexShader, GLuint fragmentShader)
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

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return program;
}

void Shader::use()
{
	glUseProgram(shaderID);
}

void Shader:: setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(shaderID, name.c_str()), (int) value);
}

void Shader::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(shaderID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(shaderID, name.c_str()), value);
}

void Shader::setMatrix(const std::string &name, glm::mat4 transformationMatrix) const
{
	glUniformMatrix4fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, glm::value_ptr(transformationMatrix));
}

unsigned int Shader::getShaderID()
{
	return shaderID;
}
