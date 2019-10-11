#include "object.h"

CObject::~CObject()
{
	m_camera = nullptr;
}

void CObject::Initialise(float _x, float _y, float _z, float _scale, float _angle, CCamera * _gameCam)
{
	m_x = _x;
	m_y = _y;
	m_z = _z;
	m_angle = _angle;
	m_scaleX = _scale;
	m_scaleY = _scale;
	m_scaleZ = _scale;
	// increase numObjects for next time an object is initialised
	numObjects++;

	m_camera = _gameCam;
	active = true;
}

float CObject::getX()
{
	return m_x;
}

float CObject::getY()
{
	return m_y;
}

float CObject::getZ()
{
	return m_z;
}

float CObject::getAngle()
{
	return m_angle;
}

float CObject::getScaleX()
{
	return m_scaleX;
}

float CObject::getScaleY()
{
	return m_scaleY;
}

float CObject::getScaleZ()
{
	return m_scaleZ;
}


bool CObject::isActive()
{
	return active;
}

void CObject::setX(float _num)
{
	m_x = _num;
}

void CObject::setY(float _num)
{
	m_y = _num;
}

void CObject::setZ(float _num)
{
	m_z = _num;
}

void CObject::setAngle(float _num)
{
	m_angle = _num;
}

void CObject::setScaleX(float _num)
{
	m_scaleX = _num;
}

void CObject::setScaleY(float _num)
{
	m_scaleY = _num;
}

void CObject::setScaleZ(float _num)
{
	m_scaleZ = _num;
}

void CObject::setScale(float _num)
{
	m_scaleX = _num;
	m_scaleY = _num;
	m_scaleZ = _num;
}

void CObject::setActive(bool _isActive)
{
	active = _isActive;
}

void CObject::keepInMap()
{
	if (m_x > Utils::LEVEL_WIDTH*0.5f)
	{
		m_x = Utils::LEVEL_WIDTH*0.5f;
	}
	if (m_x < -(Utils::LEVEL_WIDTH)*0.5f)
	{
		m_x = -(Utils::LEVEL_WIDTH)*0.5f;
	}


	if (m_z > Utils::LEVEL_HEIGHT*0.5f)
	{
		m_z = Utils::LEVEL_HEIGHT*0.5f;
	}
	if (m_z < -(Utils::LEVEL_HEIGHT)*0.5f)
	{
		m_z = -(Utils::LEVEL_HEIGHT)*0.5f;
	}
}

bool CObject::checkInMap()
{
	if (m_x > Utils::LEVEL_WIDTH*0.5 || m_x < -(Utils::LEVEL_WIDTH)*0.5 ||
		m_z > Utils::LEVEL_HEIGHT*0.5 || m_z < -(Utils::LEVEL_HEIGHT)*0.5)
	{
		return false;
	}
	else return true;
}
