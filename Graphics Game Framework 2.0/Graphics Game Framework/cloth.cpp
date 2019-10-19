#include "cloth.h"

CCloth::CCloth(GLuint _lineProgram, GLuint _pointProgram, GLuint _texture, float _width, float _height, int _numHorizontalPoints, int _numVerticalPoints)
{
	numHorizontalPoints = _numHorizontalPoints;
	numVerticalPoints = _numVerticalPoints;

	float separationX = _width / _numHorizontalPoints,
		separationY = _height / _numVerticalPoints,
		numPoints = _numHorizontalPoints * _numVerticalPoints;

	float horizontalOffset = 0.0f;
	float verticalOffset = 30.0f;

	// Initialise all the points
	for (int y = 0; y < numVerticalPoints; y++)
	{
		for (int x = 0; x < numHorizontalPoints; x++)
		{
			points.push_back(CPoint(_pointProgram, _texture, glm::vec3(x*separationX + horizontalOffset, y*separationY + verticalOffset, 0)));
			//points[x+y].m_sphere.initialise()
		}
	}


	// Make the constraints
	for (int i = 0; i < numPoints; i++)
	{
		bool
			leftCol = i % numHorizontalPoints == 0,
			rightCol = (i + 1) % numHorizontalPoints == 0,
			topRow = i < numHorizontalPoints,
			topRows = i < numHorizontalPoints * 2, // top 2 rows
			leftCols = leftCol || (i - 1) % numHorizontalPoints == 0; // 2 leftmost columns

		// vertical (up)
		if (!topRow)
			constraints.push_back(CConstraint(
				_lineProgram,
				&points[i], &points[i - numHorizontalPoints]
			));

		if (!topRows)
			constraints.push_back(CConstraint(
				_lineProgram,
				&points[i], &points[i - numHorizontalPoints * 2]
			));

		// horizontal (left)
		if (!leftCol)
			constraints.push_back(CConstraint(
				_lineProgram,
				&points[i], &points[i - 1]
			));

		if (!leftCols)
			constraints.push_back(CConstraint(
				_lineProgram,
				&points[i], &points[i - 2]
			));

		// diagonal \ 
		if (!topRow && !leftCol)
			constraints.push_back(CConstraint(
				_lineProgram,
				&points[i], &points[i - 1 - numHorizontalPoints]
			));

		// diagonal / 
		if (!topRow && !rightCol)
			constraints.push_back(CConstraint(
				_lineProgram,
				&points[i], &points[i + 1 - numHorizontalPoints]
			));
	}

}

CCloth::~CCloth()
{
	
}

void CCloth::Render(CCamera* _camera)
{
	for (auto it = points.begin(); it != points.end(); it++)
	{
		(*it).Render(_camera);
	}

	for (auto it = constraints.begin(); it != constraints.end(); it++)
	{
		(*it).Render(_camera);
	}
}
