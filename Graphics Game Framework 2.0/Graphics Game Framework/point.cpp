#include "point.h"

//CPoint::CPoint(GLuint _program, GLuint _texture, glm::vec3 _pos)
//{
//	pos = _pos;
//	m_sphere.initialise(_program, _texture, 0.0f, 0.0f, 0.1f);
//	m_sphere.setPos(_pos);
//}

CPoint::CPoint(GLuint _program, GLuint _texture, glm::vec3 _pos, float _damping, float _mass)
{
	pos = _pos;
	m_sphere.initialise(_program, _texture, 0.0f, 0.0f, 0.1f);
	m_sphere.setPos(_pos);
	damping = _damping;
	mass = _mass;
}

void CPoint::Update(float _deltaTime)
{
	if (!isStatic)
	{
		// apply force
		glm::vec3 temp = pos;
		pos += (pos - lastPos) * damping + (force / mass)*(_deltaTime);
		lastPos = temp;
		force = glm::vec3(0, 0, 0);
	}
	m_sphere.setPos(pos);
}

void CPoint::Move(glm::vec3 _delta)
{
	if (isStatic) return;
	pos += _delta;
}

void CPoint::Render(CCamera* _camera)
{
	m_sphere.Render(_camera);
}
