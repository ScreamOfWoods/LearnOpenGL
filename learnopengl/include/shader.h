#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
	private:
		unsigned int shaderID;

		GLuint createShader(GLenum shaderType, GLsizei n, const GLchar** source);
		int createShaderProgram(GLuint vertexShader, GLuint fragmentShader);
	public:
		Shader(const char* vertexPath, const char* fragmentPath);
		~Shader();
		void use();
		void setBool(const std::string &name, bool value) const;
		void setInt(const std::string &name, int value) const;
		void setFloat(const std::string &name, float value) const;
		void setMatrix(const std::string &name, glm::mat4 transformationMatrix) const;
		unsigned int getShaderID();
};

#endif //SHADER_H
