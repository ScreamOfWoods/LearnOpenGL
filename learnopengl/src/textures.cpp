#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <textures.h>
#include <iostream>
#include <glad/glad.h>

struct imageProperties loadTextureImage(std::string texturePath)
{
	struct imageProperties imageProp;
	stbi_set_flip_vertically_on_load(true);

	imageProp.data = stbi_load(texturePath.c_str(), &(imageProp.width), &(imageProp.height), &(imageProp.nrChannels), 0);

	if(!imageProp.data)
	{
		std::cout<<"Failed to load texture\n";
		exit(EXIT_FAILURE);
	}

	return imageProp;
}

unsigned int applyTexture(std::string texturePath, GLenum format)
{
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	struct imageProperties imageProp;
	//Load texture image file
	imageProp = loadTextureImage(texturePath);
	glTexImage2D(GL_TEXTURE_2D, 0, format, imageProp.width, imageProp.height, 0, format, GL_UNSIGNED_BYTE, imageProp.data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(imageProp.data);

	return texture;
}
