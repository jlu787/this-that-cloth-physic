#pragma once
#include <glm.hpp> // Matrix
#include <gtc/matrix_transform.hpp> // Matrix
#include <gtc/type_ptr.hpp> // Matrix
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <map>
//#include <cmath>

#include "object.h"
//#include "missile.h"
#include "audio.h"
#include "camera.h"
#include "ShaderLoader_Complete.h"
#include "TextLabel.h"
#include "inputController.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "enemy1.h"
#include "cubemap.h"
#include "quad.h"
#include "terrain.h"
#include "geometrymodel.h"
#include "tessmodel.h"

#pragma region DEFINES
// Models


#pragma endregion the defines used to load and access models, textures, and shaders in their arrays



//// for objects
//#define BACKGROUND	0
//#define PLAYER		1
//#define COIN		2
//
//// enemy1 moves around the perimeter of the grid
//#define ENEMY1		3
//
//// enemy2 moves randomly in the diagonal part of the grid
//#define ENEMY2		4
//
//#define LOSESCREEN	5
//
//#define BLANK		6

class CGame
{
public:
	CGame();
	~CGame();

	void Initialise();
	void Render();
	void Update();

	float getDeltaTime();

	void ResetGame();

	void ProcessDeltaTime();

	void DrawScaledUp(CShape * _object, float _scale);

	// MOVE BACK to private later
	CCamera m_camera;
	CCamera m_canvas;
	CInputController m_inputController;

private:
	std::map<string, GLuint> m_PROGRAMS;
	std::map<string, GLuint> m_TEXTURES;
	std::map<string, GLuint> m_MODELS;
	CPlayer m_player;

	//CObject m_objects[50];
	CAudioManager m_audio;
	//CCamera m_camera;
	GLuint m_program;

	float deltaTime;
	float previousTimeStamp;
	float elapsedTime; // used to check how long player has been playing

	// TEXT
	//TextLabel* menuStart;
	//TextLabel* menuExit;
	//TextLabel* scoreText;
	//TextLabel* healthText;
	//TextLabel* fpsCounter;

	// vector of objects
	//std::vector<CBullet*> vecBullets;
	//std::vector<CEnemy*> vecEnemy;

	// GAME STATE VARIABLES

	bool gameLost = false;
	bool inMenu = true;

	// BACKGROUND ETC..
	Terrain m_terrain;
	GeometryModel m_star;
	TessModel m_tesselatedModel;


	/*CReflectiveSphere m_reflectiveSphere;
	CCubeMap m_cubeMap;
	CQuad m_floor;
	CQuad m_water;
	CCube testCube;
	CCube m_stencilCube;*/
	//std::vector <CCube*> vecGridBorder;

	/*CCube zoomIn;
	CCube zoomOut;*/

	// MOUSE PICKING
	glm::vec3 rayDirection;
	float mouseY;
	float mouseX;
	bool UpdateMousePicking(CShape * _object);

};
