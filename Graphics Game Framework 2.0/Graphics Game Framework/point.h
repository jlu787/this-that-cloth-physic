#pragma once
#include "Utility.h"
#include "Sphere.h"

class CPoint
{
public:
	//CPoint(glm::vec3 _pos);
	CPoint() {};
	CPoint(GLuint _program, GLuint _texture, glm::vec3 _pos, float _damping, float _mass);

	~CPoint() {};

	bool isStatic = false;
	glm::vec3 force;
	glm::vec3 pos;
	glm::vec3 lastPos;

	float mass;
	float damping;

	void Update(float _deltaTime);

	void Move(glm::vec3 _delta);
	void Render(CCamera* _camera);

	CSphere m_sphere;

private:

};