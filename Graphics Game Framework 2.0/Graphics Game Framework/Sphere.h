#pragma once

#include <glew.h>
#include <freeglut.h>

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include "shapes.h"
#include "ShaderLoader_Complete.h"

class CSphere: public CShape
{
public:
	CSphere();
	~CSphere();

	void initialise(GLuint _program, GLuint _texture, int _x, int _y, float _scale);
	void Render(CCamera* _gameCam);
	 
protected:


	//GLuint VAO;

	GLuint IndiceCount;
	int DrawType;
};

