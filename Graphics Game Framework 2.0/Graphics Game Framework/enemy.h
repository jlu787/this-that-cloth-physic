#pragma once

#include "object.h"

class CEnemy : public CObject
{
public:
	CEnemy();
	~CEnemy();

	static const float shotDelay;

	//static const float maxSpeed;
	//static const float maxForce;
	//static const float wanderDistance;
	//static const float wanderRadius;

	// getters
	bool getCanFire() { return m_canFire; }

	// setters

	virtual void Update(float _deltaTime) = 0;
	virtual void Render() = 0;
	void enemyFire(); // used to set variables associated with fire

protected:
	float m_shotTimer = 0.0f; // to calculate when to fire
	bool m_canFire = false;

};
