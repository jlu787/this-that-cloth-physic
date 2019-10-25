#pragma once

#include "Utility.h"
#include "point.h"
#include "line.h"

class CConstraint
{
private:
	float rest_distance; // the length between particle p1 and p2 in rest configuration

public:
	CPoint *p1, *p2; // the two particles that are connected through this constraint

	CConstraint(CPoint *p1, CPoint *p2, GLuint _lineProgram, bool _shouldRender) : p1(p1), p2(p2)
	{
		glm::vec3 vec = p1->getPos() - p2->getPos();
		rest_distance = glm::length(vec);

		shouldRender = _shouldRender;

		if (_shouldRender)
		{
			m_line.initailise(_lineProgram, p1->getPos(), p2->getPos());
		}
	}

	~CConstraint()
	{
		if (p1 != nullptr) delete p1;
		if (p2 != nullptr) delete p2;
	}

	CLine m_line;
	bool shouldRender = false;

	/* This is one of the important methods, where a single constraint between two particles p1 and p2 is solved
	the method is called by Cloth.time_step() many times per frame*/
	void satisfyConstraint()
	{
		glm::vec3 p1_to_p2 = p2->getPos() - p1->getPos(); // vector from p1 to p2
		float current_distance = glm::length(p1_to_p2); // current distance between p1 and p2
		glm::vec3 correctionVector = p1_to_p2 * (1 - rest_distance / current_distance); // The offset vector that could moves p1 into a distance of rest_distance to p2
		glm::vec3 correctionVectorHalf = correctionVector * 0.5f; // Lets make it half that length, so that we can move BOTH p1 and p2.
		p1->offsetPos(correctionVectorHalf); // correctionVectorHalf is pointing from p1 to p2, so the length should move p1 half the length needed to satisfy the constraint.
		p2->offsetPos(-correctionVectorHalf); // we must move p2 the negative direction of correctionVectorHalf since it points from p2 to p1, and not p1 to p2.

		// update the line positions
		if (shouldRender)
		{
			m_line.m_pos1 = p1->getPos();
			m_line.m_pos2 = p2->getPos();
		}
	}
};

