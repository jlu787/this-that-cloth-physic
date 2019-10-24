#pragma once

#include "Utility.h"
#include "point.h"
#include "line.h"

class CConstraint
{
public:
	//CConstraint() {};
	CConstraint(CPoint* _p1, CPoint* _p2);

	~CConstraint() {};

	CConstraint(GLuint _program, CPoint * _p1, CPoint * _p2);

	void Satisfy();
	void Render(CCamera * _camera);
	//void Render();
private:
	CPoint *p1, *p2;
	float distance;
	float stiffness = 0.8f;
	CLine line;

	//const float stiffness = 0.8f;
};

