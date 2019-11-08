#pragma once
#include "Utility.h"
#include "Sphere.h"

class CPoint
{
public:
	CPoint(glm::vec3 pos, GLuint _program, GLuint _texture, int _x, int _y) : pos(pos), old_pos(pos), acceleration(glm::vec3(0, 0, 0)), mass(1), movable(true)/*, accumulated_normal(glm::vec3(0, 0, 0))*/
	{
		m_sphere.initialise(_program, _texture, 0, 0, SPHERE_SCALE);
		m_sphere.setPos(pos);
		x = _x;
		y = _y;
	}
	CPoint() {};

	// used to store index of point
	int x;
	int y;

	// burning
	bool onFire = false;

	CSphere m_sphere;

	void addForce(glm::vec3 f);

	/* This is one of the important methods, where the time is progressed a single step size (TIME_STEPSIZE)
	   The method is called by Cloth.time_step()
	   Given the equation "force = mass * acceleration" the next position is found through verlet integration*/
	void timeStep();

	glm::vec3& getPos() { return pos; }

	void setPos(glm::vec3 _pos) { pos = _pos; m_sphere.setPos(_pos); }

	void offsetPos(const glm::vec3 v) { if (movable) pos += v; }

	void SetMovable(bool _b) { movable = _b; }
	bool GetMovable() { return movable; }

	bool beingDragged = false; // used to check if a point is being dragged

private:
	bool movable; // can the point move or not ? used to pin parts of the cloth

	float mass; // the mass of the point
	glm::vec3 pos; // the current position of the point in 3D space
	glm::vec3 old_pos; // the position of the point in the previous time step, used as part of the verlet numerical integration scheme
	glm::vec3 acceleration; // a vector representing the current acceleration of the point
};