#pragma once

#include "shapes.h"

class CLine : public CShape
{
public:
	void initailise(GLuint _program, glm::vec3 _pos1, glm::vec3 _pos2);
	void Render(CCamera* _camera);

	glm::vec3 m_pos1;
	glm::vec3 m_pos2;
	glm::vec3 m_color = glm::vec3(0.0f, 0.0f, 1.0f);

private:
	// vertices for a horizontal line
	GLfloat vertices[12]{
		// Position				// Color
		 0.0f,  0.0f, 0.0f,		0.0f, 1.0f, 0.0f,	
		 1.0f,  0.0f, 0.0f,		0.0f, 1.0f, 0.0f,	
	};
};
