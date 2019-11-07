#include "shapes.h"


#pragma region GETTERS AND SETTERS
float CShape::getPosX()
{
	return m_posX;
}

float CShape::getPosY()
{
	return m_posY;
}

float CShape::getPosZ()
{
	return m_posZ;
}

glm::vec3 CShape::getPos()
{
	return glm::vec3(m_posX, m_posY, m_posZ);
}

float CShape::getScaleX()
{
	return m_scaleX;
}

float CShape::getScaleY()
{
	return m_scaleY;
}

float CShape::getScaleZ()
{
	return m_scaleZ;
}

float CShape::getRotX()
{
	return m_rotX;
}

float CShape::getRotY()
{
	return m_rotY;
}

float CShape::getRotZ()
{
	return m_rotZ;
}

glm::mat4 CShape::getModelMatrix()
{
	// Translation

	glm::vec3 objPosition = glm::vec3(m_posX, m_posY, m_posZ); // This is how much you will translate by
	glm::mat4 translationMatrix = glm::translate(glm::mat4(), objPosition); // create the transformation matrix

																			// Rotation
	glm::vec3 rotationAxis = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::mat4 rotationX = glm::rotate(glm::mat4(), glm::radians(m_rotX), rotationAxis);

	rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 rotationY = glm::rotate(glm::mat4(), glm::radians(m_rotY), rotationAxis);

	rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::mat4 rotationZ = glm::rotate(glm::mat4(), glm::radians(m_rotZ), rotationAxis);

	// Scaling
	glm::vec3 objScale = glm::vec3(m_scaleX, m_scaleY, m_scaleZ);
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(), objScale);

	// Getting model matrix
	glm::mat4 model = translationMatrix * rotationX * rotationY * rotationZ * scaleMatrix;

	return model;
}

bool CShape::getActive()
{
	return m_active;
}

void CShape::setPosX(float _pos)
{
	m_posX = _pos;
}

void CShape::setPosY(float _pos)
{
	m_posY = _pos;
}

void CShape::setPosZ(float _pos)
{
	m_posZ = _pos;
}

void CShape::setPos(glm::vec3 _pos)
{
	m_posX = _pos.x;
	m_posY = _pos.y;
	m_posZ = _pos.z;
}

void CShape::setScaleX(float _scale)
{
	m_scaleX = _scale;
}

void CShape::setScaleY(float _scale)
{
	m_scaleY = _scale;
}

void CShape::setScaleZ(float _scale)
{
	m_scaleZ = _scale;
}

void CShape::setRotX(float _rot)
{
	m_rotX = _rot;
}

void CShape::setRotY(float _rot)
{
	m_rotY = _rot;
}

void CShape::setRotZ(float _rot)
{
	m_rotZ = _rot;
}
void CShape::setActive(bool _b)
{
	m_active = _b;
}
#pragma endregion


