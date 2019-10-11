#pragma once
#include "object.h"
#include "Model.h"
#include "quad.h"

class CPlayer: public CObject
{
public:
	CPlayer();
	~CPlayer();

	void Update(float _deltaTime);
	void Render();

	// getters
	int getHealth() { return m_health; }
	int getScore() { return m_score; }
	bool getCanFire(){ return m_canFire; } // used to check if player is ready to fire
	bool getCanParry() { return m_canParry; }
	float getParryScale() { return m_parryScale; }

	// setters
	void setModel();
	void setQuad(GLuint _program, GLuint _texture);
	void setScore(int _score) { m_score = _score; }
	void setHealth(int _health) { m_health = _health; }
	void addScore(int _num) { m_score += _num; }
	void reduceHealth() { m_health--; };
	void ResetPlayer();

	// PLAYER CONTROLS
	void playerMoveUp(float _deltaTime);
	void playerMoveDown(float _deltaTime);
	void playerMoveRight(float _deltaTime);
	void playerMoveLeft(float _deltaTime);

	// used to reset shot timer
	void playerFire();

	// used to reset parry timer
	void playerParry();

private:
	Model* m_model = nullptr;
	CQuad* m_quad = nullptr;

	// PLAYER VARIABLES
	float m_playerSpeed = 10.0f;
	int m_health = 3;
	int m_score = 0;

	// shooting
	bool m_canFire = true;
	float m_shotTimer = 0.5f;
	float m_shotDelay = 0.5f; // how long in seconds before the player can shoot again

	// parrying
	bool m_canParry = true;
	bool m_parrying = false;
	float m_parryScale = 5.0f;
	float m_parryTimer = 1.0f;
	float m_parryCoolDown = 3.0f;
	float m_parryRenderTimer = 0.0f;
	float m_parryRenderTime = 0.35f;
	
};