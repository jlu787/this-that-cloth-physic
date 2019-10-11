#pragma once

#include "ShaderLoader_Complete.h"
#include "shapes.h"
#include "camera.h"

class CQuad : public CShape
{
public:
	void initialise(GLuint _program, GLuint _texture, float _x, float _y, float _scale);
	void Render(CCamera* _gameCam);


private:
	// indices for rendering a quad
	GLuint indices[6] = {
		0, 1, 2,	// First triangle
		0, 2, 3,	// Second triangle
	};

	// vertices for a basic quad
	GLfloat vertices[32]{
		// Position				// Color			// Texture
		-0.5f,  0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f,	// Top-Left
		-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 1.0f,	// Bot-Left
		0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 0.0f,	1.0f, 1.0f,	// Bot-Right
		0.5f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	1.0f, 0.0f,	// Top-Right
	};

	

	// TODO test static
};
