#pragma once
#include "object.h"
#include "sphereReflective.h"

enum BULLET_TYPE
{
	ALLY = 0,
	ENEMY,
};

class CBullet: public CObject
{
public:
	CBullet() {};
	CBullet(GLuint _program, GLuint _texture);
	CBullet(GLuint _program, GLuint _texture, float _x, float _y, float _z);
	~CBullet();

	glm::vec3 getVelocity() { return m_velocity; };
	bool getActive() { return m_active; };
	BULLET_TYPE getType() { return m_type; }

	void setVelocity(glm::vec3 _velocity) { m_velocity = _velocity; };
	void setActive(bool _b) { m_active = _b; };
	void setType(BULLET_TYPE _type) { m_type = _type; }
	void setProgram(GLuint _program) { m_shape->setProgram(_program); };

	void Update(float _deltaTime);
	void Render();
private:
	float m_speed = 10.0f;

	// this should be a normalised direction vector it will be scaled up by speed
	glm::vec3 m_velocity;
	bool m_active;
	CSphere* m_shape = nullptr;
	BULLET_TYPE m_type;
};