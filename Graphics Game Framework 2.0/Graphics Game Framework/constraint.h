#pragma once

#include "Utility.h"
#include "point.h"

class CConstraint
{
public:
	//CConstraint() {};
	CConstraint(CPoint* _p1, CPoint* _p2);

	~CConstraint() {};

	void Satisfy();
	void Render(CCamera * m_camera);
	//void Render();
private:
	CPoint *p1, *p2;
	float distance;

	//const float stiffness = 0.8f;
};

