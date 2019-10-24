#pragma once

#include <vector>

#include "Utility.h"
#include "point.h"
#include "constraint.h"

class CCloth
{
public:

	CCloth() {};
	
	CCloth(GLuint _lineProgram, GLuint _pointProgram, GLuint _texture, float _width, float _height, int _numHorizontalPoints, int _numVerticalPoints, float _damping, float _weight);
	~CCloth();

	void Render(CCamera * _camera);

	std::vector<CPoint> points;
	std::vector<CConstraint> constraints;

	void Update(float _deltaTime);

	glm::vec3 gravity = glm::vec3(0.0f, -0.3f, 0.0f);

private:
	int numHorizontalPoints;
	int numVerticalPoints;

};
