#pragma once

#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include "camera.h"

// simple shape class
class CShape
{
public:
	// getters
	float getPosX();
	float getPosY();
	float getPosZ();
	glm::vec3 getPos();
	float getScaleX();
	float getScaleY();
	float getScaleZ();
	float getRotX();
	float getRotY();
	float getRotZ();
	
	bool getActive();

	// setters
	void setPosX(float _pos);
	void setPosY(float _pos);
	void setPosZ(float _pos);
	void setPos(glm::vec3 _pos);
	void setScaleX(float _scale);
	void setScaleY(float _scale);
	void setScaleZ(float _scale);
	void setRotX(float _rot);
	void setRotY(float _rot);
	void setRotZ(float _rot);
	void setActive(bool _b);
	void setProgram(GLuint _program) { m_program = _program; }
	void setTexture(GLuint _texture) { m_tex = _texture; }

	virtual void Render(CCamera* _gameCam) = 0;

	static int numObjects;

protected:
	float m_posX = 0.0f;
	float m_posY = 0.0f;
	float m_posZ = 0.0f;
	float m_scaleX = 1.0f;
	float m_scaleY = 1.0f;
	float m_scaleZ = 1.0f;
	float m_rotX = 0.0f;
	float m_rotY = 0.0f;
	float m_rotZ = 0.0f;

	GLuint m_program;
	GLuint m_VAO;
	GLuint m_VBO;
	GLuint m_EBO;
	GLuint m_tex;

	bool m_active;

private:
};