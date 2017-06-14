#include "texture.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>
Texture::Texture(const std::string& fileName)
{
	int width, height, numComponents;
	unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);	// load texture

	if (imageData == NULL)
	{
		std::cerr << "Texture loading failed for texture: " << fileName << std::endl;
	}

	glGenTextures(1, &m_texture);	// generate 1 texture from the image file

	glBindTexture(GL_TEXTURE_2D, m_texture);	// specifiy the texture type and bind it
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Sets behaviour for texture wrapping - so if texture repeats when it goes out of bounds
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Set behaviour for situations where image resolution doesnt take up the same screen resolution space due to being at an angle
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	
		
		
	stbi_image_free(imageData);	// delete from cpu
}


Texture::~Texture()
{
	glDeleteTextures(1, &m_texture);
}


void Texture::Bind(unsigned int unit)
{

	assert(unit >= 0 && unit <= 31);

	glActiveTexture(GL_TEXTURE + unit);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}