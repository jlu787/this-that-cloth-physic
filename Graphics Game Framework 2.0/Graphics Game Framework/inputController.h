#pragma once
#include <glew.h>
#include <freeglut.h>
#include <iostream>

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

private:
	int mouseX, mouseY;

	
	

};