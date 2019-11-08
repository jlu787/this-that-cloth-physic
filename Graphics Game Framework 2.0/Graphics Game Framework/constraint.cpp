#include "constraint.h"

//CConstraint::CConstraint(GLuint _program, CPoint * _p1, CPoint * _p2)
//{
//	p1 = _p1;
//	p2 = _p2;
//	distance = glm::length(p1->pointPos - p2->pointPos);
//	line.initailise(_program, p1->pointPos, p2->pointPos);
//}
//
//void CConstraint::Satisfy()
//{
//
//	if (p1 != nullptr && p2 != nullptr)
//	{
//		/*glm::vec3 v = p1->pointPos - p2->pointPos;
//		v *= ((1.0f - distance / glm::length(v)) * stiffness);
//		p1->Move(-v);
//		p2->Move(v);*/
//
//		glm::vec3 v = line.m_pos1 - line.m_pos2;
//		v *= ((1.0f - distance / glm::length(v)) * stiffness);
//		line.m_pos1 -= v;
//		line.m_pos2 += v;
//		p1->pointPos = line.m_pos1;
//		p2->pointPos = line.m_pos2;
//
//		p1->m_sphere.setPos(p1->pointPos);
//		p2->m_sphere.setPos(p2->pointPos);
//
//		/*glm::vec3 delta = p2->pos - p1->pos;
//		float deltaLength = delta.length();
//		float difference = (deltaLength - distance) / deltaLength;
//		float im1 = 1 / p1->mass;
//		float im2 = 1 / p2->mass;
//
//		p1->pos -= delta * (im1 / (im1 + im2)) * stiffness * difference;
//		p2->pos += delta * (im2 / (im1 + im2)) * stiffness * difference;*/
//
//		/*p1->m_sphere.setPos(p1->pos);
//		p2->m_sphere.setPos(p2->pos);*/
//	}
//
//	
//}
//
//void CConstraint::Render(CCamera* _camera)
//{
//	//glBegin(GL_LINES);
//	//glm::mat4 mvp;
//	//glm::vec4 p1_pos = glm::vec4(p1->pos, 1.0f);
//	//glm::vec4 p2_pos = glm::vec4(p2->pos, 1.0f);
//
//	//glm::vec3 somePos1 = glm::vec3(0.0f, 0.0f, 0.0f);
//	//glm::vec3 somePos2 = glm::vec3(1.0f, 0.0f, 0.0f);
//
//
//	//glVertex3fv(glm::value_ptr(somePos1));
//	//glVertex3fv(glm::value_ptr(somePos2));
//	//glEnd();
//
//	// UNCOMMENT TO FEEL THE LAG
//	//line.Render(_camera);
//}

void CConstraint::satisfyConstraint(bool _canBeTorn)
{
	if (p1 != nullptr && p2 != nullptr)
	{

		// update the line positions if this a constraint we want to render
		if (shouldRender)
		{
			m_line.m_pos1 = p1->getPos();
			m_line.m_pos2 = p2->getPos();
		}


		glm::vec3 differenceVector = p2->getPos() - p1->getPos(); // vector from p1 to p2
		float current_distance = glm::length(differenceVector); // current distance between p1 and p2

		// check if it has been torn by checking distance
		if (current_distance >= restingLength * 3.0f && _canBeTorn)
		{
			p1 = nullptr;
			p2 = nullptr;
			shouldRender = false;
		}

		// satisfy constraints based on how far they are from one another
		else
		{
			glm::vec3 correctionVector = differenceVector * (1 - restingLength / current_distance); // The offset vector that could moves p1 into a distance of rest_distance to p2
			glm::vec3 correctionVectorHalf = correctionVector * 0.5f; // Lets make it half that length, so that we can move BOTH p1 and p2.
			p1->offsetPos(correctionVectorHalf * (float)STIFFNESS); // correctionVectorHalf is pointing from p1 to p2, so the length should move p1 half the length needed to satisfy the constraint.
			p2->offsetPos(-correctionVectorHalf * (float)STIFFNESS); // we must move p2 the negative direction of correctionVectorHalf since it points from p2 to p1, and not p1 to p2.

			// burning
			if (p1->onFire || p2->onFire /*&& burntness < 1.0f*/)
			{
				burntness += 0.0025f * burnRate/current_distance;
			}
			// spread
			if (burntness >= 0.5f)
			{
				p1->onFire = true;
				p2->onFire = true;
			}

			// break
			if (burntness >= 1.0f)
			{
				p1 = nullptr;
				p2 = nullptr;
			}

			burntness = glm::clamp(burntness, 0.0f, 1.0f);
			m_line.m_color = glm::vec3(burntness, 0.0f, 1.0f - burntness);
		}
		

		
	
	}
	else
	{
		shouldRender = false;
	}



}
