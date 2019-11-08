#pragma once

#include <vector>

#include "Utility.h"
#include "point.h"
#include "constraint.h"

class CCloth
{
public:
	CCloth() {};
	~CCloth();
	CCloth(float width, float height, int num_particles_width, int num_particles_height, GLuint _lineProgram, GLuint _sphereProgram, GLuint _sphereTex) : numHorizontalParticles(num_particles_width), numVerticalParticles(num_particles_height)
	{
		m_lineProgram = _lineProgram;

		points.resize(num_particles_width*num_particles_height); 

		float horizontalOffset = 0.0f,
			verticalOffset = 30.0f,
			depthOffset = 0.0f;

		// creating particles in a grid of particles from (0,0,0) to (width,-height,0)
		for (int x = 0; x < num_particles_width; x++)
		{
			for (int y = 0; y < num_particles_height; y++)
			{
				glm::vec3 pos = glm::vec3(width * (x / (float)num_particles_width) + horizontalOffset,
					-height * (y / (float)num_particles_height) + verticalOffset,
					depthOffset);
				points[y*num_particles_width + x] = CPoint(pos, _sphereProgram, _sphereTex, x, y); // insert particle in column x at y'th row
			}
		}

		// Connecting immediate neighbor particles (i.e. diagonal, vertical and horizontal neighbors)
		for (int x = 0; x < num_particles_width; x++)
		{
			for (int y = 0; y < num_particles_height; y++)
			{
				if (x < num_particles_width - 1) makeConstraint(getParticle(x, y), getParticle(x + 1, y), true);
				if (y < num_particles_height - 1) makeConstraint(getParticle(x, y), getParticle(x, y + 1), true);
				if (x < num_particles_width - 1 && y < num_particles_height - 1) makeConstraint(getParticle(x, y), getParticle(x + 1, y + 1), true);
				if (x < num_particles_width - 1 && y < num_particles_height - 1) makeConstraint(getParticle(x + 1, y), getParticle(x, y + 1), true);
			}
		}

		// making the upper row static
		for (int i = 0; i < num_particles_width; i++)
		{
			if (i % 2 == 0)
			{
				getParticle(0 + i, 0)->SetMovable(false);
			}
		}

		//for (int i = 0; i < constraints.size(); i++)
		//{
		//	constraints[i].p1 = nullptr;
		//}

		//for (int i = 400; i < 485; i++)
		//{
		//	constraints[i].p1 = nullptr;
		//}

		// TOP LEFT AND TOP RIGHT STATIC
		//getParticle(0, 0)->offsetPos(glm::vec3(-0.5, 0.0, 0.0));
		//getParticle(0, 0)->makeUnmovable();

		//getParticle(num_particles_width-1, 0)->offsetPos(glm::vec3(-0.5, 0.0, 0.0));
		//getParticle(num_particles_width-1, 0)->makeUnmovable();
	}

	float ground = 0.0f; // y value for the ground
	bool canBeTorn = false;

	void GroundCheck();

	GLuint m_lineProgram;

	
	//this function makes all the points movable
	void Release();
	bool released = false;

	void SlideRings(float _delta);

	//goes through a timeStep for the cloth by first satisfying the constraints and then performing verlet integration on all the particles
	void timeStep();

	//this function adds a force to all points 
	void addForce(const glm::vec3 direction);

	//used to add wind forces to all particles, is added for each triangle since the final force is proportional to the triangle area as seen from the wind direction
	void windForce(const glm::vec3 direction);

	void Render(CCamera* _camera);

	int numHorizontalParticles;
	int numVerticalParticles;

	std::vector<CPoint> points; // all particles that are part of this cloth
	std::vector<CConstraint> constraints; // all constraints between points as part of this cloth

	CPoint* getParticle(int x, int y) { return &points[y*numHorizontalParticles + x]; }

	void addWindForceForPoint(int _x, int _y, glm::vec3 direction);


private:

	void makeConstraint(CPoint *p1, CPoint *p2, bool _shouldRender) { constraints.push_back(CConstraint(p1, p2, m_lineProgram, _shouldRender)); }

	/*  
	calculate normal vector of the triangle defined by the position of the particles p1, p2, and p3.
	The magnitude of the normal vector is equal to the area of the parallelogram defined by p1, p2 and p3
	*/
	glm::vec3 calcTriangleNormal(CPoint *p1, CPoint *p2, CPoint *p3);

	/* A private method used by windForce() to calcualte the wind force for a single triangle
	defined by p1,p2,p3*/
	void addWindForcesForTriangle(CPoint *p1, CPoint *p2, CPoint *p3, const glm::vec3 direction);
};
