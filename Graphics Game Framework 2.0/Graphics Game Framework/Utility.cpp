#include "Utility.h"

const float Utils::LEVEL_WIDTH = 30.0f;
const float Utils::LEVEL_HEIGHT = 30.0f;

GLuint Utils::loadTexture(const char * _file)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int width, height;
	unsigned char* image = SOIL_load_image(_file, &width, &height, 0, SOIL_LOAD_RGBA); // Load Image
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);	// Create texture with the loaded data

	glGenerateMipmap(GL_TEXTURE_2D);	// Generate Mipmap
	SOIL_free_image_data(image);		// Free memory

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	return (texture);
}
