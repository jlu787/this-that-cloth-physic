#pragma once

#pragma once

#include "ShaderLoader_Complete.h"

#include "shapes.h"

class CCube : public CShape
{

public:
	//void initialise(GLuint _program, GLuint _texture, int _x, int _y, float _scale);
	void initialise(GLuint _program, GLuint _texture, float _x, float _y, float _z, float _scale);
	void Render(CCamera* _gameCam);


private:
	// indices for rendering a quad
	GLuint indices[36] = {
		 0,  1,  2, // Front
		 0,  2,  3, // Front

		 7,  6,  5, // Back
		 7,  5,  4, // Back

		 8,  9, 10, // Left
		 8, 10, 11, // Left

		12, 13, 14, // Right
		12, 14, 15, // Right

		16, 17, 18, // Top
		16, 18, 19, // Top

		20, 21, 22, // Bottom
		20, 22, 23, // Bottom
	};

	// vertices for a basic quad
	GLfloat vertices[24*11]{
		// Positions			// Colors			// Tex Coords	// Normals
		// Front
		-0.5f,  0.5f,  0.5f,	0.0f, 1.0f, 0.0f,	0.0f, 0.0f,		0.0f, 0.0f, 1.0f,	// 0
		-0.5f, -0.5f,  0.5f,	0.0f, 1.0f, 0.0f,	0.0f, 1.0f,		0.0f, 0.0f, 1.0f,	// 1
		 0.5f, -0.5f,  0.5f,	0.0f, 1.0f, 0.0f,	1.0f, 1.0f,		0.0f, 0.0f, 1.0f,	// 2
		 0.5f,  0.5f,  0.5f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f,		0.0f, 0.0f, 1.0f,	// 3

		// Back
		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f,		0.0f, 0.0f, -1.0f,	// 4
		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 0.0f,	1.0f, 1.0f,		0.0f, 0.0f, -1.0f,	// 5
		 0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 0.0f,	0.0f, 1.0f,		0.0f, 0.0f, -1.0f,	// 6
		 0.5f,  0.5f, -0.5f,	0.0f, 1.0f, 0.0f,	0.0f, 0.0f,		0.0f, 0.0f, -1.0f,	// 7

		// Left
		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f, 0.0f,	0.0f, 0.0f,		-1.0f, 0.0f, 0.0f,	// 8
		-0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 0.0f,	0.0f, 1.0f,		-1.0f, 0.0f, 0.0f,	// 9
		-0.5f, -0.5f,  0.5f,	0.0f, 1.0f, 0.0f,	1.0f, 1.0f,		-1.0f, 0.0f, 0.0f,	// 10
		-0.5f,  0.5f,  0.5f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f,		-1.0f, 0.0f, 0.0f,	// 11

		// Right
		 0.5f,	0.5f,  0.5f,	0.0f, 1.0f, 0.0f,	0.0f, 0.0f,		1.0f, 0.0f, 0.0f,	// 12
		 0.5f, -0.5f,  0.5f,	0.0f, 1.0f, 0.0f,	0.0f, 1.0f,		1.0f, 0.0f, 0.0f,	// 13
		 0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 0.0f,	1.0f, 1.0f,		1.0f, 0.0f, 0.0f,	// 14
		 0.5f,	0.5f, -0.5f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f,		1.0f, 0.0f, 0.0f,	// 15

		 // Top
		-0.5f,  0.5f, -0.5f,	0.0f, 1.0f, 0.0f,	0.0f, 0.0f,		0.0f, 1.0f, 0.0f,	// 16
		-0.5f,  0.5f,  0.5f,	0.0f, 1.0f, 0.0f,	0.0f, 1.0f,		0.0f, 1.0f, 0.0f,	// 17
		 0.5f,  0.5f,  0.5f,	0.0f, 1.0f, 0.0f,	1.0f, 1.0f,		0.0f, 1.0f, 0.0f,	// 18
		 0.5f,  0.5f, -0.5f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f,		0.0f, 1.0f, 0.0f,	// 19

		 // Bottom
		 -0.5f, -0.5f,  0.5f,	0.0f, 1.0f, 0.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,	// 20
		 -0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 0.0f,	0.0f, 1.0f, 	0.0f, -1.0f, 0.0f,	// 21
		  0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 0.0f,	1.0f, 1.0f, 	0.0f, -1.0f, 0.0f,	// 22
		  0.5f, -0.5f,  0.5f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f, 	0.0f, -1.0f, 0.0f,	// 23
	};



};
