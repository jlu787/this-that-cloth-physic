#include "point.h"

CPoint::CPoint(GLuint _program, GLuint _texture, glm::vec3 _pos)
{
	pos = _pos;
	m_sphere.initialise(_program, _texture, 0.0f, 0.0f, 0.1f);
	m_sphere.setPos(_pos);
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
