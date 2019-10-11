#pragma once

#include "cube.h"
#include "pyramid.h"
#include "enemy.h"

class CEnemy1 : public CEnemy
{
public:
	CEnemy1() {};
	~CEnemy1();

	void Initialise(GLuint _program, GLuint _texture, CCamera * _gameCam);
	void Update(float _deltaTime);
	void Render();

private:
	CPyramid * m_shape;
};
