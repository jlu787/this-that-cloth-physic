#pragma once

#include "Utility.h"
#include "point.h"
#include "line.h"

class CConstraint
{
public:
	CPoint *p1, *p2; // the two points that are connected through this constraint

	CConstraint(CPoint *p1, CPoint *p2, GLuint _lineProgram, bool _shouldRender) : p1(p1), p2(p2)
	{
		glm::vec3 diff = p1->getPos() - p2->getPos();
		restingLength = glm::length(diff);

		shouldRender = _shouldRender;

		if (_shouldRender)
		{
			m_line.initailise(_lineProgram, p1->getPos(), p2->getPos());
		}

		burnRate = (float)(rand() % 500) / 1000.0f + 0.75f; // add some randomness to burnRate (from 0.75 - 1.25)
	}

	~CConstraint()
	{
		/*if (p1 != nullptr) delete p1;
		if (p2 != nullptr) delete p2;*/
	}

	CLine m_line;
	bool shouldRender = false;
	float burntness = 0.0f;
	float burnRate = 1.0f;
	//bool onFire = false;

	/* This is one of the important methods, where a single constraint between two points p1 and p2 is solved
	the method is called by Cloth.time_step() many times per frame*/
	void satisfyConstraint(bool _canBeTorn);

private:
	float restingLength; // the length between point p1 and p2 in rest configuration


};

