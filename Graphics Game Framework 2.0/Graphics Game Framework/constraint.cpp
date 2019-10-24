#include "constraint.h"

CConstraint::CConstraint(GLuint _program, CPoint * _p1, CPoint * _p2)
{
	p1 = _p1;
	p2 = _p2;
	distance = glm::length(p1->pos - p2->pos);
	line.initailise(_program, p1->pos, p2->pos);
}

void CConstraint::Satisfy()
{


	/*glm::vec3 v = p1->pos - p2->pos;
	v *= ((1.0f - distance / glm::length(v)) * stiffness);
	p1->Move(-v);
	p2->Move(v);*/

	glm::vec3 delta = p2->pos - p1->pos;
	float deltaLength = delta.length();
	float difference = (deltaLength - distance) / deltaLength;
	float im1 = 1 / p1->mass;
	float im2 = 1 / p2->mass;

	p1->pos -= delta * (im1 / (im1 + im2)) * stiffness * difference;
	p2->pos -= delta * (im2 / (im1 + im2)) * stiffness * difference;
}

void CConstraint::Render(CCamera* _camera)
{
	//glBegin(GL_LINES);
	//glm::mat4 mvp;
	//glm::vec4 p1_pos = glm::vec4(p1->pos, 1.0f);
	//glm::vec4 p2_pos = glm::vec4(p2->pos, 1.0f);

	//glm::vec3 somePos1 = glm::vec3(0.0f, 0.0f, 0.0f);
	//glm::vec3 somePos2 = glm::vec3(1.0f, 0.0f, 0.0f);


	//glVertex3fv(glm::value_ptr(somePos1));
	//glVertex3fv(glm::value_ptr(somePos2));
	//glEnd();

	// UNCOMMENT TO FEEL THE LAG
	//line.Render(_camera);
}
