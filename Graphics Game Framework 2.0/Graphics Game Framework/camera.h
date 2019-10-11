#pragma once
#include <glew.h>
#include <freeglut.h> 
#include <glm.hpp> // Matrix
#include <gtc/matrix_transform.hpp> // Matrix
#include <gtc/type_ptr.hpp> // Matrix

#include "Utility.h"

enum CAMERATYPE
{
	ORTHOGRAPHIC,
	PERSPECTIVE,
};

class CCamera
{
public:
	CCamera() {};
	~CCamera() {};

	// Set variables for a simple 2D camera with a centered camera
	void Initialise(CAMERATYPE _type)
	{
	
		float halfScreenWidth = (float)Utils::SCR_WIDTH * 0.5f;
		float halfScreenHeight = (float)Utils::SCR_HEIGHT * 0.5f;
		switch (_type)
		{
		case (ORTHOGRAPHIC):
			// 2D pos
			camPos = glm::vec3(0.0f, 0.0f, 3.0f);
			camLookDir = glm::vec3(0.0f, 0.0f, -1.0f);
			camUpDir = glm::vec3(0.0f, 1.0f, 0.0f);

			// ortho
			proj = glm::ortho(-halfScreenWidth, halfScreenWidth, -halfScreenHeight, halfScreenHeight, 0.1f, 100.0f);

			m_type = ORTHOGRAPHIC;
			break;
		default: 
			//// 3D Pos
			//camPos = glm::vec3(0.0f, 20.0f, 0.0f);
			//camLookDir = glm::vec3(0.0f, -1.0f, 0.0f);
			//camUpDir = glm::vec3(0.0f, 0.0f, -1.0f);

				// 3D Pos
			camPos = glm::vec3(0.0f, 20.0f, 0.0f);
			camLookDir = glm::vec3(0.0f, 0.0f, 1.0f);
			camUpDir = glm::vec3(0.0f, 1.0f, 0.0f);

			//perspective
			proj = glm::perspective(45.0f, (float)Utils::SCR_WIDTH / (float)Utils::SCR_HEIGHT, 0.1f, 10000.0f);

			m_type = PERSPECTIVE;
			break;
		}

	

		// calculate view and projection matrices
		view = glm::lookAt(camPos, camPos + camLookDir, camUpDir);

		initCamPos = camPos;
	};

	glm::mat4 getViewMat() { return view; };
	glm::mat4 getProjMat() { return proj; };
	glm::vec3 getCamPos() { return camPos; };

	void setLookDir(glm::vec3 _front);
	void setCamPos(glm::vec3 _pos) { camPos = _pos; };

	void Update(float _deltaTime);

	// Processing input
	void moveForward(float _deltaTime);
	void moveBack(float _deltaTime);
	void moveRight(float _deltaTime);
	void moveLeft(float _deltaTime);

	void ResetCamera();

	float getCameraSpeed() { return cameraSpeed; }
	void setCameraSpeed(float newSpeed) { cameraSpeed = newSpeed; }

	CAMERATYPE m_type = PERSPECTIVE;

private:
	glm::vec3 camPos;
	glm::vec3 camLookDir;
	glm::vec3 camUpDir;
	glm::vec3 initCamPos;


	float cameraSpeed = 2.5f;

	float timeElapsed = 0.0f;
	// View matrix
	glm::mat4 view;

	// Projection matrix
	glm::mat4 proj;

};