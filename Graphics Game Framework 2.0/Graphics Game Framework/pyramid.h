#pragma once

#include "ShaderLoader_Complete.h"

#include "shapes.h"

class CPyramid : public CShape
{

public:
	void initialise(GLuint _program, GLuint _texture, int _x, int _y, float _scale);
	void Render(CCamera* _gameCam);


private:
	// indices for rendering a pyramid
	GLuint indices[18] = {
		0, 4, 3,	// Side 1
		3, 4, 2,	// Side 2
		2, 4, 1,	// Side 3
		1, 4, 0,	// Side 4

		1, 0, 3,	// Bottom Triangle 1
		1, 3, 2,	// Bottom Triangle 2
	};

	// vertices for a basic pyramid
	GLfloat vertices[5*11]{
		// Positions			// Colors			// Tex Coords
		-1.0f, 0.0f, -1.0f,		1.0f, 1.0f, 0.0f,	0.0f, 0.0f,		-1.0f, 0.0f, -1.0f, // 0
		-1.0f, 0.0f,  1.0f,		1.0f, 0.0f, 0.0f,	0.0f, 1.0f,		-1.0f, 0.0f,  1.0f, // 1
		 1.0f, 0.0f,  1.0f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f,		 1.0f, 0.0f,  1.0f, // 2
		 1.0f, 0.0f, -1.0f,		0.0f, 0.0f, 1.0f,	1.0f, 0.0f,		 1.0f, 0.0f, -1.0f, // 3

		0.0f, 1.0f, 0.0f,		0.0f, 1.0f, 1.0f,	0.5f, 0.5f,		 0.0f, 1.0f,  0.0f,	// 4 Top Point
	};



};