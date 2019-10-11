#include <windows.h>
//#include <vld.h>
#include <iostream>

//#include "Utility.h"
#include "ShaderLoader_Complete.h"
#include "TextLabel.h"
#include "camera.h"
#include "audio.h"
#include "gamemanager.h"
#include "quad.h"
#include "pyramid.h"
#include "cube.h"
#include "Sphere.h"
#include "cubemap.h"
#include "sphereReflective.h"
#include "Model.h"
#include "player.h"

CGame myGame;
//CCamera myCamera;
//CAudioManager myAudio;
int CObject::numObjects = 0;

// TESTING
//CQuad* newQuad;
//CPyramid* newPyramid;
//CCube* newCube;
//CSphere* newSphere;
//CCubeMap* newCubeMap;
//CReflectiveSphere* newReflectiveSphere;
//Model* newModel;
//CPlayer* newPlayer;

//int currentMouseX, currentMouseY;

void KeyboardDown(unsigned char key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);
void MousePassiveMove(int x, int y);
void MouseMove(int x, int y);
void MouseClick(int button, int state, int x, int y);
void ProcessInput();

void Render();
void Update();

void ShutDown();

int main(int argc, char **argv)
{
	// Setup and create at glut controlled window
	glutInit(&argc, argv);
	// Enable Anti Aliasing
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutSetOption(GLUT_MULTISAMPLE, 8);
	glEnable(GL_MULTISAMPLE);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(Utils::SCR_WIDTH, Utils::SCR_HEIGHT);
	glutCreateWindow("OpenGL Demo");

	// Sets up all gl function callbacks based on pc hardware
	if (glewInit() != GLEW_OK)
	{
		// If glew setup failed then application will not run graphics correctly
		std::cout << "Glew Initialization Failed. Aborting Application." << std::endl;
		system("pause");
	}

	glEnable(GL_SCISSOR_TEST);
	glScissor(0, 50, 800, 700);
	
	glClearColor(0.75f, 0.0f, 0.3f, 1.0f); // FOG
	// Sets the clear color when calling glClear()

	myGame.Initialise();

	// Register callbacks
	glutDisplayFunc(Render);
	glutIdleFunc(Update);

	glutKeyboardFunc(KeyboardDown);
	glutKeyboardUpFunc(KeyboardUp);

	glutMouseFunc(MouseClick);
	glutMotionFunc(MouseMove);
	glutPassiveMotionFunc(MousePassiveMove);

	glutCloseFunc(ShutDown);

	glutMainLoop();

	//delete label;
	return 0;
}

void Render()
{
	//glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	

	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LESS);

	myGame.Render();

	glutSwapBuffers();
}

void Update()
{
	myGame.Update();
	glutPostRedisplay();
}

void ShutDown()
{
	//myGame.ShutDown();
}

void KeyboardDown(unsigned char key, int x, int y)
{

	myGame.m_inputController.KeyboardDown(key, x, y);

}

void KeyboardUp(unsigned char key, int x, int y)
{

	myGame.m_inputController.KeyboardUp(key, x, y);
}

void ProcessInput()
{
	// Designed so that character only moves when you release button
	myGame.m_inputController.ProcessInput();
	
}

void MouseClick(int button, int state, int x, int y)
{
	myGame.m_inputController.MouseClick(button, state, x, y);
}

void MousePassiveMove(int x, int y)
{
	/*mouseX = (2.0f * x) / (float)Utils::SCR_WIDTH - 1.0f;
	mouseY = 1.0f - (2.0f * y) / (float)Utils::SCR_HEIGHT;*/
	myGame.m_inputController.MousePassiveMove(x, y);
}

void MouseMove(int x, int y)
{
	myGame.m_inputController.MouseMove(x, y);
}
