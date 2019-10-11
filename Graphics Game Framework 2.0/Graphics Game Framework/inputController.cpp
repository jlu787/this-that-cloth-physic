#include "inputController.h"

void CInputController::KeyboardDown(unsigned char key, int x, int y)
{
	KeyState[key] = INPUT_DOWN_FIRST;
	//std::cout << "Keydown : " << key << std::endl;
}

void CInputController::KeyboardUp(unsigned char key, int x, int y)
{
	KeyState[key] = INPUT_UP_FIRST;
}

void CInputController::ProcessInput()
{
	// Designed so that character only moves when you release button

	/*if (KeyState['w'] == INPUT_DOWN)
	{
		myGame.m_camera.moveForward(myGame.getDeltaTime());
	}
	if (KeyState['s'] == INPUT_DOWN)
	{
		myGame.m_camera.moveBack(myGame.getDeltaTime());
	}
	if (KeyState['d'] == INPUT_DOWN)
	{
		myGame.m_camera.moveRight(myGame.getDeltaTime());
	}
	if (KeyState['a'] == INPUT_DOWN)
	{
		myGame.m_camera.moveLeft(myGame.getDeltaTime());
	}*/

	for (int i = 0; i < 3; i++)
	{
		if (MouseState[i] == INPUT_DOWN_FIRST)
		{
			MouseState[i] = INPUT_DOWN;
		}
		else if (MouseState[i] == INPUT_UP_FIRST)
		{
			MouseState[i] = INPUT_UP;
		}
	}

	for (int i = 0; i < 256; i++)
	{
		if (KeyState[i] == INPUT_DOWN_FIRST)
		{
			KeyState[i] = INPUT_DOWN;
		}
		else if (KeyState[i] == INPUT_UP_FIRST)
		{
			KeyState[i] = INPUT_UP;
		}
	}
}

void CInputController::MouseClick(int button, int state, int x, int y)
{
	if (button >= 3) // Ensure the array is not accessed out of bounds
		return;
	//std::cout << "CALLED" << std::endl;
	MouseState[button] = (state == GLUT_DOWN) ? INPUT_DOWN_FIRST : INPUT_UP_FIRST;
}

void CInputController::MousePassiveMove(int x, int y)
{
	//std::cout << "Passive x: " << x << " | y: " << y << std::endl;
	mouseX = x;
	mouseY = y;
}

void CInputController::MouseMove(int x, int y)
{
	//std::cout << "Clicked x: " << x << " | y: " << y << std::endl;
	mouseX = x;
	mouseY = y;
}

void CInputController::PanCamera()
{
	//static float yaw, pitch;
	//if (MouseState[0] == INPUT_DOWN)
	//{
	//	float sensitivity = 2.5f * myGame.getDeltaTime();

	//	if (currentMouseX > (float)Utils::SCR_WIDTH*0.75) // pan right
	//		yaw += sensitivity;
	//	else if (currentMouseX < (float)Utils::SCR_WIDTH*0.25) // pan left
	//		yaw -= sensitivity;
	//	if (currentMouseY < (float)Utils::SCR_HEIGHT*0.25) // pan up
	//		pitch += sensitivity;
	//	else if (currentMouseY > (float)Utils::SCR_HEIGHT*0.75) // pan down
	//		pitch -= sensitivity;

	//	if (pitch > 89.0f)
	//		pitch = 89.0f;
	//	if (pitch < -89.0f)
	//		pitch = -89.0f;

	//	glm::vec3 front;
	//	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	//	front.y = sin(glm::radians(pitch));
	//	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	//	myGame.m_camera.setLookDir(glm::normalize(front));
	//}
}

int CInputController::getMouseX()
{
	// convert window coordinates to game coordinates
	return (mouseX - 400);
}

int CInputController::getMouseZ()
{
	// convert window coordinates to game coordinates
	// ON THE Z AXIS
	return (mouseY - 400);
}
int CInputController::getMouseXWindow()
{
	return mouseX;
}
int CInputController::getMouseYWindow()
{
	return mouseY;
}


