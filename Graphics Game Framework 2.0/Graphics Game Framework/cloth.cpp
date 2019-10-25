#include "cloth.h"

//CCloth::CCloth(GLuint _lineProgram, GLuint _pointProgram, GLuint _texture, float _width, float _height, int _numHorizontalPoints, int _numVerticalPoints, float _damping, float _weight)
//{
//	numHorizontalPoints = _numHorizontalPoints;
//	numVerticalPoints = _numVerticalPoints;
//
//	float separationX = _width / _numHorizontalPoints,
//		separationY = _height / _numVerticalPoints,
//		numPoints = _numHorizontalPoints * _numVerticalPoints,
//		pointMass = _weight / numPoints;
//
//	float horizontalOffset = -20.0f;
//	float verticalOffset = 55.0f;
//
//	// Initialise all the points
//	for (int y = 0; y < numVerticalPoints; y++)
//	{
//		for (int x = 0; x < numHorizontalPoints; x++)
//		{
//			points.push_back(CPoint(_pointProgram, _texture, glm::vec3(x*separationX + horizontalOffset, -y*separationY + verticalOffset, 50), _damping, pointMass));
//			//points[x+y].m_sphere.initialise()
//		}
//	}
//
//
//	//// Make the constraints
//	//// Connecting immediate neighbor particles with constraints (distance 1 and sqrt(2) in the grid)
//	//for (int x = 0; x < numHorizontalPoints; x++)
//	//{
//	//	for (int y = 0; y < numVerticalPoints; y++)
//	//	{
//	//		if (x < numHorizontalPoints - 1)  constraints.push_back(CConstraint(_lineProgram,getPoint(x, y), getPoint(x + 1, y)));
//	//		if (y < numVerticalPoints - 1) constraints.push_back(CConstraint(_lineProgram,getPoint(x, y), getPoint(x, y + 1)));
//	//		if (x < numHorizontalPoints - 1 && y < numVerticalPoints - 1) constraints.push_back(CConstraint(_lineProgram,getPoint(x, y), getPoint(x + 1, y + 1)));
//	//		if (x < numHorizontalPoints - 1 && y < numVerticalPoints - 1) constraints.push_back(CConstraint(_lineProgram,getPoint(x + 1, y), getPoint(x, y + 1)));
//	//	}
//	//}
//
//
//	//// Connecting secondary neighbors with constraints (distance 2 and sqrt(4) in the grid)
//	//for (int x = 0; x < numHorizontalPoints; x++)
//	//{
//	//	for (int y = 0; y < numVerticalPoints; y++)
//	//	{
//	//		if (x < numHorizontalPoints - 2) constraints.push_back(CConstraint(_lineProgram,getPoint(x, y), getPoint(x + 2, y)));
//	//		if (y < numVerticalPoints - 2) constraints.push_back(CConstraint(_lineProgram,getPoint(x, y), getPoint(x, y + 2)));
//	//		if (x < numHorizontalPoints - 2 && y < numVerticalPoints - 2) constraints.push_back(CConstraint(_lineProgram,getPoint(x, y), getPoint(x + 2, y + 2)));
//	//		if (x < numHorizontalPoints - 2 && y < numVerticalPoints - 2) constraints.push_back(CConstraint(_lineProgram,getPoint(x + 2, y), getPoint(x, y + 2)));
//	//	}
//	//}
//
//	for (int i = 0; i < numPoints; i++)
//	{
//		bool
//			leftCol = i % numHorizontalPoints == 0,
//			rightCol = (i + 1) % numHorizontalPoints == 0,
//			topRow = i < numHorizontalPoints,
//			topRows = i < numHorizontalPoints * 2, // top 2 rows
//			leftCols = leftCol || (i - 1) % numHorizontalPoints == 0; // 2 leftmost columns
//
//		// vertical (up)
//		if (!topRow)
//			constraints.push_back(CConstraint(
//				_lineProgram,
//				&points[i], &points[i - numHorizontalPoints]
//			));
//
//		//if (!topRows)
//		//	constraints.push_back(CConstraint(
//		//		_lineProgram,
//		//		&points[i], &points[i - numHorizontalPoints * 2]
//		//	));
//
//		// horizontal (left)
//		if (!leftCol)
//			constraints.push_back(CConstraint(
//				_lineProgram,
//				&points[i], &points[i - 1]
//			));
//
//		//if (!leftCols)
//		//	constraints.push_back(CConstraint(
//		//		_lineProgram,
//		//		&points[i], &points[i - 2]
//		//	));
//
//		//// diagonal \ 
//		//if (!topRow && !leftCol)
//		//	constraints.push_back(CConstraint(
//		//		_lineProgram,
//		//		&points[i], &points[i - 1 - numHorizontalPoints]
//		//	));
//
//		//// diagonal / 
//		//if (!topRow && !rightCol)
//		//	constraints.push_back(CConstraint(
//		//		_lineProgram,
//		//		&points[i], &points[i + 1 - numHorizontalPoints]
//		//	));
//	}
//
//	for (int i = 0; i < numHorizontalPoints; i++)
//	{
//		points[i].isStatic = true;
//	}
//
//	/*points[0].isStatic = true;
//	points[numHorizontalPoints - 1].isStatic = true;*/
//	//points[200].isStatic = true;
//}
//
//CCloth::~CCloth()
//{
//	
//}
//
//void CCloth::Render(CCamera* _camera)
//{
//	for (auto it = points.begin(); it != points.end(); it++)
//	{
//		(*it).Render(_camera);
//	}
//
//	for (auto it = constraints.begin(); it != constraints.end(); it++)
//	{
//		(*it).Render(_camera);
//	}
//}
//
//void CCloth::Update(float _deltaTime)
//{
//	// Gravity
//	for (auto it = points.begin(); it != points.end(); it++)
//	{
//		(*it).force += gravity * _deltaTime;
//	}
//
//	// Satisfy constraints
//	for (int i = 0; i < 3; i++)
//	{
//		for (auto it = constraints.begin(); it != constraints.end(); it++)
//		{
//			(*it).Satisfy();
//		}
//	}
//
//
//	// Apply Forces
//	for (auto it = points.begin(); it != points.end(); it++)
//	{
//		(*it).Update(_deltaTime);
//	}
//
//	//std::cout << points[2].pos.y << std::endl;
//}
