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


