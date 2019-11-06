#include "point.h"

//CPoint::CPoint(GLuint _program, GLuint _texture, glm::vec3 _pos)
//{
//	pos = _pos;
//	m_sphere.initialise(_program, _texture, 0.0f, 0.0f, 0.1f);
//	m_sphere.setPos(_pos);
//}

//CPoint::CPoint(GLuint _program, GLuint _texture, glm::vec3 _pos, float _damping, float _mass)
//{
//	pointPos = _pos;
//	lastPos = _pos;
//	m_sphere.initialise(_program, _texture, 0.0f, 0.0f, 0.5f);
//	m_sphere.setPos(_pos);
//	damping = _damping;
//	mass = _mass;
//}
//
//void CPoint::Update(float _deltaTime)
//{
//	if (!isStatic)
//	{
//		// apply force
//		lastPos = pointPos;
//		pointPos += (pointPos - lastPos) * (/*1.0f-*/damping) + (force / mass)*(_deltaTime);
//		force = glm::vec3(0, 0, 0);
//	}
//	m_sphere.setPos(pointPos);
//}

//
//void CPoint::Render(CCamera* _camera)
//{
//	m_sphere.Render(_camera);
//}

void CPoint::addForce(glm::vec3 f)
{
	acceleration += f / mass;

	if (glm::length(acceleration) > MAX_ACCELERATION)
	{
		acceleration = glm::normalize(acceleration) * (float)MAX_ACCELERATION;
	}
}

void CPoint::timeStep()
{
	if (movable)
	{
		glm::vec3 temp = pos;
		pos = pos + (pos - old_pos) * (float)(1.0f - DAMPING) + acceleration * (float)(TIME_STEP);
		old_pos = temp;
		acceleration = glm::vec3(0, 0, 0); // acceleration is reset since it HAS been translated into a change in position (and implicitely into velocity)	
	}
	m_sphere.setPos(pos);
}
