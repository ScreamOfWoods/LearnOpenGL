#ifndef TEXTURES_H
#define TEXTURES_H
#include <glad/glad.h>
#include <iostream>

struct imageProperties
{
	int width;
	int height;
	int nrChannels;
	unsigned char* data;
};

struct imageProperties loadTextureImage(std::string texturePath, GLenum format);
unsigned int applyTexture(std::string texturePath, GLenum format);

#endif //TEXTURES_H
