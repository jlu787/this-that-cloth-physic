#include "bullet.h"

CBullet::CBullet(GLuint _program, GLuint _texture)
{
	m_shape = new CSphere();
	m_shape->initialise(_program, _texture, 0, 0, 1.0f);

	m_shape->setPosX(m_x);
	m_shape->setPosY(m_y);
	m_shape->setPosZ(m_z);
}

CBullet::CBullet(GLuint _program, GLuint _texture, float _x, float _y, float _z)
{
	m_shape = new CSphere();
	m_shape->initialise(_program, _texture, 0, 0, 1.0f);

	m_x = _x;
	m_y = _y;
	m_z = _z;
	m_shape->setPosX(m_x);
	m_shape->setPosY(m_y);
	m_shape->setPosZ(m_z);
}

CBullet::~CBullet()
{
}

void CBullet::Update(float _deltaTime)
{
	m_x += m_velocity.x * _deltaTime * m_speed;
	m_y += m_velocity.y * _deltaTime * m_speed;
	m_z += m_velocity.z * _deltaTime * m_speed;

	m_shape->setPosX(m_x);
	m_shape->setPosY(m_y);
	m_shape->setPosZ(m_z);
}

void CBullet::Render()
{
	m_shape->Render(m_camera);
}
