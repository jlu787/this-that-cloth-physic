#pragma once
#include <glew.h>
#include <freeglut.h>
#include <iostream>
#include "Utility.h"

enum InputMouse
{
	MOUSE_LEFT,
	MOUSE_MIDDLE,
	MOUSE_RIGHT,
};

enum InputState
{
	INPUT_UP,
	INPUT_DOWN,
	INPUT_UP_FIRST,
	INPUT_DOWN_FIRST,
};

class CInputController
{
public:
	void KeyboardDown(unsigned char key, int x, int y);
	void KeyboardUp(unsigned char key, int x, int y);
	void ProcessInput();
	void MouseClick(int button, int state, int x, int y);
	void MousePassiveMove(int x, int y);
	void MouseMove(int x, int y);
	void PanCamera();

	InputState KeyState[255];
	InputState MouseState[3];

	int getMouseX();
	int getMouseZ();
	int getMouseXWindow();
	int getMouseYWindow();
	glm::vec2 GetMouseNDC();

	//bool UpdateMousePickingSphere(CCamera* _camera, CSphere* _sphere)
	//{
	//	// screen pos
	//	glm::vec2 normalizedScreenPos = GetMouseNDC();

	//	// screenpos to Proj Space
	//	glm::vec4 clipCoords = glm::vec4(normalizedScreenPos.x, normalizedScreenPos.y, -1.0f, 1.0f);

	//	// proj space to eye space
	//	glm::mat4 invProjMat = glm::inverse(camera->GetProjMatrix());

	//	glm::vec4 eyeCoords = invProjMat * clipCoords;
	//	eyeCoords = glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);

	//	//eyespace to world space
	//	glm::mat4 invViewMat = glm::inverse(camera->getViewMatrix());
	//	glm::vec4 rayWorld = invViewMat * eyeCoords;
	//	glm::vec3 rayDirection = glm::normalize(glm::vec3(rayWorld));

	//	// code to check intersection with sphere
	//	float radius = 1.0f;
	//	glm::vec3 v = sphere->getPosition() - camera->getCameraPos();

	//	float a = glm::dot(rayDirection, rayDirection);
	//	float b = 2 * glm::dot(v, rayDirection);
	//	float c = glm::dot(v, v) - radius * radius;
	//	float d = b * b - 4 * a* c;
	//	if (d > 0) {
	//		float x1 = (-b - sqrt(d)) / 2;
	//		float x2 = (-b + sqrt(d)) / 2;
	//		if (x1 >= 0 && x2 >= 0) return true; // intersects
	//		if (x1 < 0 && x2 >= 0) return true; // intersects
	//	}
	//	else if (d <= 0) {
	//		return false;// no intersection
	//	}
	//}

private:
	int mouseX, mouseY;

	
	

};