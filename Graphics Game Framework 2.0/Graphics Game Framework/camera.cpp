#include "camera.h"

void CCamera::setLookDir(glm::vec3 _front)
{
	camLookDir = _front;
}

void CCamera::Update(float _deltaTime)
{
	//// ROTATING AROUND BASED ON TIME

	//// View Matrix
	//timeElapsed += _deltaTime;
	//GLfloat radius = 2.0f;
	//camPos.x = sin(timeElapsed) * radius;
	//camPos.y = 1.5f;
	//camPos.z = cos(timeElapsed)	* radius;

	//view = glm::lookAt(
	//	camPos, 
	//	glm::vec3(0.0f, 0.0f, 0.0f),
	//	camUpDir
	//);

	view = glm::lookAt(camPos, camPos + camLookDir, camUpDir);
}

void CCamera::moveForward(float _deltaTime)
{
	camPos += cameraSpeed * camLookDir * _deltaTime;
}

void CCamera::moveBack(float _deltaTime)
{
	camPos -= cameraSpeed * camLookDir * _deltaTime;
}

void CCamera::moveRight(float _deltaTime)
{
	camPos += glm::normalize(glm::cross(camLookDir, camUpDir)) * cameraSpeed * _deltaTime;
}

void CCamera::moveLeft(float _deltaTime)
{
	camPos -= glm::normalize(glm::cross(camLookDir, camUpDir)) * cameraSpeed * _deltaTime;
}

void CCamera::ResetCamera()
{
	camPos = initCamPos;
}
