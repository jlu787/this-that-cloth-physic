#pragma once

#include <vector>

#include "Utility.h"
#include "point.h"
#include "constraint.h"

class CCloth
{
public:
	//CCloth(float _width, float _height, int _numHorizontalPoints, int _numVerticalPoints);
	CCloth() {};
	CCloth(GLuint _program, GLuint _texture, float _width, float _height, int _numHorizontalPoints, int _numVerticalPoints);
	~CCloth();

	void Render(CCamera * _camera);

	std::vector<CPoint> points;
	std::vector<CConstraint> constraints;


private:
	int numHorizontalPoints;
	int numVerticalPoints;

};
