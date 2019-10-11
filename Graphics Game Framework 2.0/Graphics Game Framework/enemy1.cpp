#include "enemy1.h"

CEnemy1::~CEnemy1()
{
	delete m_shape;
}

void CEnemy1::Initialise(GLuint _program, GLuint _texture, CCamera* _gameCam)
{
	m_shape = new CPyramid();
	m_shape->initialise(_program, _texture, 0.0f, 0.0f, 1.0f);
	m_shape->setPosX(m_x);
	m_shape->setPosY(m_y);
	m_shape->setPosZ(m_z);
	m_camera = _gameCam;
}

void CEnemy1::Update(float _deltaTime)
{
	m_shotTimer += _deltaTime;

	if (m_shotTimer >= CEnemy::shotDelay)
	{
		m_canFire = true;
	}
}

void CEnemy1::Render()
{
	m_shape->Render(m_camera);
}
