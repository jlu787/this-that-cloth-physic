#include "enemy.h"

const float CEnemy::shotDelay = 1.0f;

CEnemy::CEnemy()
{
}

CEnemy::~CEnemy()
{
}

void CEnemy::Update(float _deltaTime)
{
}

void CEnemy::Render()
{
}

void CEnemy::enemyFire()
{
	m_shotTimer = 0.0f;
	m_canFire = false;
}
