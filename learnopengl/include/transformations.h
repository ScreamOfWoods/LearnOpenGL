#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


glm::mat4 rotate(glm::mat4 transformationMatrix, glm::vec3 rotationAxis, float degree);

glm::mat4 translate(glm::mat4 transformationMatrix, glm::vec3 position);

glm::mat4 scale(glm::mat4 transformationMatrix, glm::vec3 multiplier);

void setClippingPlane(Shader* shader, float fieldOfView, glm::vec3 rotationVector, 
		glm::vec3 depthVector, float aspectRatio, float nearPlane, float farPlane);

void applyTransformations(glm::mat4 transformationMatrix, Shader* shaderProgram, std::string uniformName);

#endif //TRANSFORMATIONS_H
