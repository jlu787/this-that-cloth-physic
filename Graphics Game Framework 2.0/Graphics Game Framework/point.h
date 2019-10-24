#pragma once
#include "Utility.h"
#include "Sphere.h"

class CPoint
{
public:
	//CPoint(glm::vec3 _pos);
	CPoint() {};
	CPoint(GLuint _program, GLuint _texture, glm::vec3 _pos);

	~CPoint() {};

	bool isStatic;
	glm::vec3 pos;
	glm::vec3 lastPos;

	float mass;

	void Update(float _deltaTime);

	void Move(glm::vec3 _delta);
	void Render(CCamera* _camera);

	CSphere m_sphere;

private:

};