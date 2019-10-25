#pragma once

#include <vector>

#include "Utility.h"
#include "point.h"
#include "constraint.h"

class CCloth
{
public:
	CCloth() {};

	/* This is a important constructor for the entire system of particles and constraints*/
	CCloth(float width, float height, int num_particles_width, int num_particles_height, GLuint _lineProgram, GLuint _sphereProgram, GLuint _sphereTex) : num_particles_width(num_particles_width), num_particles_height(num_particles_height)
	{
		m_lineProgram = _lineProgram;

		points.resize(num_particles_width*num_particles_height); //I am essentially using this vector as an array with room for num_particles_width*num_particles_height particles

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
				points[y*num_particles_width + x] = CPoint(pos, _sphereProgram, _sphereTex); // insert particle in column x at y'th row
			}
		}

		// Connecting immediate neighbor particles with constraints (distance 1 and sqrt(2) in the grid)
		for (int x = 0; x < num_particles_width; x++)
		{
			for (int y = 0; y < num_particles_height; y++)
			{
				if (x < num_particles_width - 1) makeConstraint(getParticle(x, y), getParticle(x + 1, y), true);
				if (y < num_particles_height - 1) makeConstraint(getParticle(x, y), getParticle(x, y + 1), true);
				if (x < num_particles_width - 1 && y < num_particles_height - 1) makeConstraint(getParticle(x, y), getParticle(x + 1, y + 1), false);
				if (x < num_particles_width - 1 && y < num_particles_height - 1) makeConstraint(getParticle(x + 1, y), getParticle(x, y + 1), false);
			}
		}


		// Connecting secondary neighbors with constraints (distance 2 and sqrt(4) in the grid)
		for (int x = 0; x < num_particles_width; x++)
		{
			for (int y = 0; y < num_particles_height; y++)
			{
				if (x < num_particles_width - 2) makeConstraint(getParticle(x, y), getParticle(x + 2, y), false);
				if (y < num_particles_height - 2) makeConstraint(getParticle(x, y), getParticle(x, y + 2), false);
				if (x < num_particles_width - 2 && y < num_particles_height - 2) makeConstraint(getParticle(x, y), getParticle(x + 2, y + 2), false);
				if (x < num_particles_width - 2 && y < num_particles_height - 2) makeConstraint(getParticle(x + 2, y), getParticle(x, y + 2), false);
			}
		}


		// making the upper left most three and right most three particles unmovable
		//for (int i = 0; i < 3; i++)
		//{
		//	getParticle(0 + i, 0)->offsetPos(glm::vec3(0.5, 0.0, 0.0)); // moving the particle a bit towards the center, to make it hang more natural - because I like it ;)
		//	getParticle(0 + i, 0)->makeUnmovable();

		//	getParticle(0 + i, 0)->offsetPos(glm::vec3(-0.5, 0.0, 0.0)); // moving the particle a bit towards the center, to make it hang more natural - because I like it ;)
		//	getParticle(num_particles_width - 1 - i, 0)->makeUnmovable();
		//}

		// making the upper row
		for (int i = 0; i < num_particles_width - 1; i++)
		{
			getParticle(0 + i, 0)->SetMovable(false);
		}

		// TOP LEFT AND TOP RIGHT STATIC
		//getParticle(0, 0)->offsetPos(glm::vec3(-0.5, 0.0, 0.0));
		//getParticle(0, 0)->makeUnmovable();

		//getParticle(num_particles_width-1, 0)->offsetPos(glm::vec3(-0.5, 0.0, 0.0));
		//getParticle(num_particles_width-1, 0)->makeUnmovable();
	}

	float ground = 0.0f;

	void GroundCheck();

	GLuint m_lineProgram;

	/* drawing the cloth as a smooth shaded (and colored according to column) OpenGL triangular mesh
	Called from the display() method
	The cloth is seen as consisting of triangles for four particles in the grid as follows:

	(x,y)   *--* (x+1,y)
			| /|
			|/ |
	(x,y+1) *--* (x+1,y+1)

	*/
	//void drawShaded()
	//{
	//	// reset normals (which where written to last frame)
	//	std::vector<CPoint>::iterator particle;
	//	for (particle = particles.begin(); particle != particles.end(); particle++)
	//	{
	//		(*particle).resetNormal();
	//	}

	//	//create smooth per particle normals by adding up all the (hard) triangle normals that each particle is part of
	//	for (int x = 0; x < num_particles_width - 1; x++)
	//	{
	//		for (int y = 0; y < num_particles_height - 1; y++)
	//		{
	//			glm::vec3 normal = calcTriangleNormal(getParticle(x + 1, y), getParticle(x, y), getParticle(x, y + 1));
	//			getParticle(x + 1, y)->addToNormal(normal);
	//			getParticle(x, y)->addToNormal(normal);
	//			getParticle(x, y + 1)->addToNormal(normal);

	//			normal = calcTriangleNormal(getParticle(x + 1, y + 1), getParticle(x + 1, y), getParticle(x, y + 1));
	//			getParticle(x + 1, y + 1)->addToNormal(normal);
	//			getParticle(x + 1, y)->addToNormal(normal);
	//			getParticle(x, y + 1)->addToNormal(normal);
	//		}
	//	}

	//	glBegin(GL_TRIANGLES);
	//	for (int x = 0; x < num_particles_width - 1; x++)
	//	{
	//		for (int y = 0; y < num_particles_height - 1; y++)
	//		{
	//			glm::vec3 color(0, 0, 0);
	//			if (x % 2) // red and white color is interleaved according to which column number
	//				color = glm::vec3(0.6f, 0.2f, 0.2f);
	//			else
	//				color = glm::vec3(1.0f, 1.0f, 1.0f);

	//			drawTriangle(getParticle(x + 1, y), getParticle(x, y), getParticle(x, y + 1), color);
	//			drawTriangle(getParticle(x + 1, y + 1), getParticle(x + 1, y), getParticle(x, y + 1), color);
	//		}
	//	}
	//	glEnd();
	//}

	/*
	this function makes all the points movable
	*/

	void Release();

	/* this is an important methods where the time is progressed one time step for the entire cloth.
	This includes calling satisfyConstraint() for every constraint, and calling timeStep() for all particles
	*/
	void timeStep();

	/* used to add gravity (or any other arbitrary vector) to all particles*/
	void addForce(const glm::vec3 direction);

	/* used to add wind forces to all particles, is added for each triangle since the final force is proportional to the triangle area as seen from the wind direction*/
	void windForce(const glm::vec3 direction);

	///* used to detect and resolve the collision of the cloth with the ball.
	//This is based on a very simples scheme where the position of each particle is simply compared to the sphere and corrected.
	//This also means that the sphere can "slip through" if the ball is small enough compared to the distance in the grid bewteen particles
	//*/
	//void ballCollision(const glm::vec3 center, const float radius)
	//{
	//	std::vector<CPoint>::iterator particle;
	//	for (particle = particles.begin(); particle != particles.end(); particle++)
	//	{
	//		glm::vec3 v = (*particle).getPos() - center;
	//		float l = v.length();
	//		if (v.length() < radius) // if the particle is inside the ball
	//		{
	//			(*particle).offsetPos(v.normalized()*(radius - l)); // project the particle to the surface of the ball
	//		}
	//	}
	//}

	void Render(CCamera* _camera);

private:

	int num_particles_width; // number of particles in "width" direction
	int num_particles_height; // number of particles in "height" direction
	// total number of particles is num_particles_width*num_particles_height

	std::vector<CPoint> points; // all particles that are part of this cloth
	std::vector<CConstraint> constraints; // alle constraints between particles as part of this cloth

	CPoint* getParticle(int x, int y) { return &points[y*num_particles_width + x]; }
	void makeConstraint(CPoint *p1, CPoint *p2, bool _shouldRender) { constraints.push_back(CConstraint(p1, p2, m_lineProgram, _shouldRender)); }


	/* A private method used by drawShaded() and addWindForcesForTriangle() to retrieve the
	normal vector of the triangle defined by the position of the particles p1, p2, and p3.
	The magnitude of the normal vector is equal to the area of the parallelogram defined by p1, p2 and p3
	*/
	glm::vec3 calcTriangleNormal(CPoint *p1, CPoint *p2, CPoint *p3);

	/* A private method used by windForce() to calcualte the wind force for a single triangle
	defined by p1,p2,p3*/
	void addWindForcesForTriangle(CPoint *p1, CPoint *p2, CPoint *p3, const glm::vec3 direction);

	///* A private method used by drawShaded(), that draws a single triangle p1,p2,p3 with a color*/
	//void drawTriangle(CPoint *p1, CPoint *p2, CPoint *p3, const glm::vec3 color)
	//{
	//	glColor3fv((GLfloat*)&color);

	//	glNormal3fv((GLfloat *) &(glm::normalize(p1->getNormal())));
	//	glVertex3fv((GLfloat *) &(p1->getPos()));

	//	glNormal3fv((GLfloat *) &(glm::normalize(p2->getNormal())));
	//	glVertex3fv((GLfloat *) &(p2->getPos()));

	//	glNormal3fv((GLfloat *) &(glm::normalize(p3->getNormal())));
	//	glVertex3fv((GLfloat *) &(p3->getPos()));
	//}


};
