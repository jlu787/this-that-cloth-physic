#include "cloth.h"

void CCloth::GroundCheck()
{
	for (auto &point : points)
	{
		if (point.getPos().y < ground)
		{
			point.setPos(glm::vec3(point.getPos().x, ground, point.getPos().z));
		}
	}
}

void CCloth::Release()
{
	for (auto &point : points)
	{
		point.SetMovable(true);
	}
}

void CCloth::timeStep()
{
	std::vector<CConstraint>::iterator constraint;
	for (int i = 0; i < CONSTRAINT_ITERATIONS; i++) // iterate over all constraints several times
	{
		for (constraint = constraints.begin(); constraint != constraints.end(); constraint++)
		{
			(*constraint).satisfyConstraint(); // satisfy constraint.
		}
	}

	std::vector<CPoint>::iterator particle;
	for (particle = points.begin(); particle != points.end(); particle++)
	{
		(*particle).timeStep(); // calculate the position of each particle at the next time step.
	}
}

void CCloth::addForce(const glm::vec3 direction)
{
	std::vector<CPoint>::iterator particle;
	for (particle = points.begin(); particle != points.end(); particle++)
	{
		(*particle).addForce(direction); // add the forces to each particle
	}
}

void CCloth::windForce(const glm::vec3 direction)
{
	for (int x = 0; x < num_particles_width - 1; x++)
	{
		for (int y = 0; y < num_particles_height - 1; y++)
		{
			addWindForcesForTriangle(getParticle(x + 1, y), getParticle(x, y), getParticle(x, y + 1), direction);
			addWindForcesForTriangle(getParticle(x + 1, y + 1), getParticle(x + 1, y), getParticle(x, y + 1), direction);
		}
	}
}

void CCloth::Render(CCamera * _camera)
{
	for (auto it = points.begin(); it != points.end(); it++)
	{
		(*it).m_sphere.Render(_camera);
	}

	for (auto it = constraints.begin(); it != constraints.end(); it++)
	{
		if ((*it).shouldRender)
		{
			(*it).m_line.Render(_camera);
		}
	}
}

glm::vec3 CCloth::calcTriangleNormal(CPoint * p1, CPoint * p2, CPoint * p3)
{
	glm::vec3 pos1 = p1->getPos();
	glm::vec3 pos2 = p2->getPos();
	glm::vec3 pos3 = p3->getPos();

	glm::vec3 v1 = pos2 - pos1;
	glm::vec3 v2 = pos3 - pos1;

	return glm::cross(v1, v2);
}

void CCloth::addWindForcesForTriangle(CPoint * p1, CPoint * p2, CPoint * p3, const glm::vec3 direction)
{
	glm::vec3 normal = calcTriangleNormal(p1, p2, p3);
	glm::vec3 d = glm::normalize(normal);
	glm::vec3 force = normal * glm::dot(d, direction);
	p1->addForce(force);
	p2->addForce(force);
	p3->addForce(force);
}
