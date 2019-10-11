#pragma once
#include "glew.h"
#include "freeglut.h"
#include "shapes.h"
#include <SOIL.h> // Image loader


class CObject
{
public:
	CObject() {};
	~CObject();
	static int numObjects;

	//virtual void Initialise(float _x, float _y, float _z, float _scale, CCamera* _gameCam);
	virtual void Initialise(float _x, float _y, float _z, float _scale, float _angle, CCamera * _gameCam);
	float getX();
	float getY();
	float getZ();
	float getAngle();
	float getScaleX();
	float getScaleY();
	float getScaleZ();
	bool isActive();

	void setX(float _num);
	void setY(float _num);
	void setZ(float _num);
	void setAngle(float _num);
	void setScaleX(float _num);
	void setScaleY(float _num);
	void setScaleZ(float _num);
	void setScale(float _num);
	void setActive(bool _isActive);

	bool checkInMap();

protected:
	float m_x;
	float m_y;
	float m_z;
	float m_angle = 0.0f;
	float m_scaleX;
	float m_scaleY;
	float m_scaleZ;
	bool active = false;
	CCamera* m_camera = nullptr;

	void keepInMap();
	
};

