#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include <shader.h>
#include <transformations.h>


glm::mat4 rotate(glm::mat4 transformationMatrix, glm::vec3 rotationAxis, float degree)
{
	transformationMatrix = glm::rotate(transformationMatrix, glm::radians(degree), rotationAxis);

	return transformationMatrix;
}

glm::mat4 translate(glm::mat4 transformationMatrix, glm::vec3 position)
{
	transformationMatrix = glm::translate(transformationMatrix, position);

	return transformationMatrix;
}

glm::mat4 scale(glm::mat4 transformationMatrix, glm::vec3 multiplier)
{
	transformationMatrix = glm::scale(transformationMatrix, multiplier);

	return transformationMatrix;
}

void applyTransformations(glm::mat4 transformationMatrix, Shader* shaderProgram, std::string uniformName)
{
	shaderProgram->setMatrix(uniformName, transformationMatrix);
}
