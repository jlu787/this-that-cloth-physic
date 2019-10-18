#include "constraint.h"

CConstraint::CConstraint(CPoint * _p1, CPoint * _p2)
{
	p1 = _p1;
	p2 = _p2;
	distance = glm::length(p1->pos - p2->pos);
}

void CConstraint::Satisfy()
{
	const float stiffness = 0.8f;

	glm::vec3 v = p1->pos - p2->pos;
	v *= ((1.0f - distance / glm::length(v)) * stiffness);
	p1->Move(-v);
	p2->Move(v);
}

void CConstraint::Render(CCamera* m_camera)
{
	glBegin(GL_LINES);
	glm::mat4 mvp;
	glm::vec4 p1_pos;
	glm::vec4 p2_pos;



	glVertex3fv(glm::value_ptr(p1->pos));
	glVertex3fv(glm::value_ptr(p2->pos));
	glEnd();
}
