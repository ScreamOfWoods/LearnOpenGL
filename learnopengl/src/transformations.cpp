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

void setClippingPlane(Shader* shader, float fieldOfView, glm::vec3 rotationVector, float angle,
		glm::vec3 depthVector, float aspectRatio, float nearPlane, float farPlane)
{
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	glm::mat4 viewMatrix = glm::mat4(1.0f);
	glm::mat4 projectionMatrix = glm::mat4(1.0f);

	modelMatrix = rotate(modelMatrix, rotationVector, angle);
	viewMatrix = translate(viewMatrix, depthVector);
	projectionMatrix = glm::perspective(glm::radians(fieldOfView), aspectRatio, nearPlane, farPlane);

	shader->setMatrix("model", modelMatrix);
	shader->setMatrix("view", viewMatrix);
	shader->setMatrix("projection", projectionMatrix);
}

void applyTransformations(glm::mat4 transformationMatrix, Shader* shaderProgram, std::string uniformName)
{
	shaderProgram->setMatrix(uniformName, transformationMatrix);
}
