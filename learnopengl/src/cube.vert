#version 330 core

layout (location = 0) in vec3 coordinates;
layout (location = 1) in vec3 colour;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 colorCoord;

void main()
{
	gl_Position = projection * view * model * vec4(coordinates, 1.0f);
	colorCoord = colour;
}
