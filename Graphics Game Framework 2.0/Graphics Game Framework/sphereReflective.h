#pragma once

#include "Sphere.h"

class CReflectiveSphere : public CSphere
{
public:
	CReflectiveSphere();
	~CReflectiveSphere();

	void initialise(GLuint _program, GLuint _texture, float _x, float _y, float _scale);

	//void initialise(GLuint _program, GLuint _texture, int _x, int _y, float _scale);

	void Render(CCamera* _gameCam, unsigned int _skyboxTexID);

private:
};