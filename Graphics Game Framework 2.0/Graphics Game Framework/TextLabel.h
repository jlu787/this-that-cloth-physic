
#pragma once

// Dependency Includes
#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H  

// Library Includes
#include <map>
#include <string>
#include <iostream>

// Local Includes
//#include "ShaderLoader.h"
#include "ShaderLoader_Complete.h"
#include "Utility.h"


struct FontChar
{
	GLuint		TextureID;	// Texture ID 
	glm::ivec2	Size;		// Size of the glyph
	glm::ivec2  Bearing;	// Offset of the glyph (top left) from the baseline
	GLuint		Advance;	// How far to move for the next character
};

class TextLabel {
public:
	TextLabel() {};
	TextLabel(
		std::string text, 
		std::string font, 
		glm::vec2 pos, 
		glm::vec3 color		= glm::vec3(1.0f, 1.0f, 1.f), 
		float scale			= 1.0f);

	~TextLabel() {};

	void Render();
	void SetText(std::string newText) { text = newText; };
	void SetColor(glm::vec3 newColor) { color = newColor; };
	void SetScale(GLfloat newScale) { scale = newScale; };
	void SetPosition(glm::vec2 newPosition) { position = newPosition; };

private:
	GLuint GenerateTexture(FT_Face face);

	std::string text;
	GLfloat scale;
	glm::vec3 color;
	glm::vec2 position;
	
	GLuint VAO, VBO, program;
	glm::mat4 proj;
	std::map<GLchar, FontChar> Characters;
};
