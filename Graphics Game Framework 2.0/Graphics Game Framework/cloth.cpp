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
	released = true;
	for (auto &point : points)
	{
		point.SetMovable(true);
	}
}

void CCloth::SlideRings(float _delta)
{
	float minDistanceBetweenRings = 0.5f;
	if (!released)
	{
		// making the upper row static
		for (int i = 1; i < numHorizontalParticles; i++)
		{
			float distanceBetweenRing = 0.0f;
			if (i - 2 > 0)
			{
				distanceBetweenRing = glm::distance(getParticle(i, 0)->getPos(), getParticle(i - 2, 0)->getPos());
			}
			
			if (!getParticle(i, 0)->GetMovable() && distanceBetweenRing > minDistanceBetweenRings)
			getParticle(i, 0)->setPos(glm::vec3(getParticle(i, 0)->getPos().x + _delta, getParticle(i,0)->getPos().y, getParticle(i, 0)->getPos().z));
		}
	}
}

void CCloth::timeStep()
{
	for (int i = 0; i < CONSTRAINT_ITERATIONS; i++) // iterate over all constraints several times
	{
		for (auto &constraint : constraints)
		{
			constraint.satisfyConstraint();
		}
	}

	for (auto &point : points)
	{
		point.timeStep();
	}
}

void CCloth::addForce(const glm::vec3 direction)
{
	for (auto &point : points)
	{
		point.addForce(direction);
	}
}

void CCloth::windForce(const glm::vec3 direction)
{
	for (int x = 0; x < numHorizontalParticles - 1; x++)
	{
		for (int y = 0; y < numVerticalParticles - 1; y++)
		{
			// adds wind force for 2 triangles making a quadrant of the cloth
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
