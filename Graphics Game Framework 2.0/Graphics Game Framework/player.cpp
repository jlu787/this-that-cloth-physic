#include "player.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	delete m_model;
}

void CPlayer::Update(float _deltaTime)
{
	m_shotTimer += _deltaTime;
	m_parryTimer += _deltaTime;

	if (m_shotTimer >= m_shotDelay && !m_canFire)
	{
		m_canFire = true;
	}

	if (m_parryTimer >= m_parryCoolDown && !m_canParry)
	{
		m_canParry = true;
	}

	if (m_parrying)
	{
		m_parryRenderTimer += _deltaTime;
		if (m_parryRenderTimer >= m_parryRenderTime)
		{
			m_parrying = false;
		}
	}

	keepInMap();
}

void CPlayer::Render()
{
	m_model->Render(glm::vec3(m_x, m_y, m_z), m_angle, glm::vec3(m_scaleX, m_scaleY, m_scaleZ));

	if (m_parrying)
	{
		m_quad->Render(m_camera);
	}
}

void CPlayer::setModel()
{
	m_model = new Model("Resources/Models/Tank/Tank.obj", m_camera);
}

void CPlayer::setQuad(GLuint _program, GLuint _texture)
{
	if (m_quad != nullptr) delete m_quad;
	m_quad = new CQuad();
	m_quad->initialise(_program, _texture, 0.0f, 0.0f, m_parryScale);
	m_quad->setPosX(m_x);
	m_quad->setPosY(m_y);
	m_quad->setPosZ(m_z);
	m_quad->setRotX(-90.0f);
}

void CPlayer::ResetPlayer()
{
	m_health = 3;
	m_score = 0;
	m_x = 0.0f;
	m_y = 0.0f;
	m_z = 0.0f;
}

void CPlayer::playerMoveUp(float _deltaTime)
{
	m_z -= m_playerSpeed * _deltaTime;
}

void CPlayer::playerMoveDown(float _deltaTime)
{
	m_z += m_playerSpeed * _deltaTime;
}

void CPlayer::playerMoveRight(float _deltaTime)
{
	m_x += m_playerSpeed * _deltaTime;
}

void CPlayer::playerMoveLeft(float _deltaTime)
{
	m_x -= m_playerSpeed * _deltaTime;
}

void CPlayer::playerFire()
{
	m_shotTimer = 0.0f;
	m_canFire = false;
}

void CPlayer::playerParry()
{
	m_parryTimer = 0.0f;
	m_parryRenderTimer = 0.0f;
	m_parrying = true;
	m_canParry = false;
}
