#include "gamemanager.h"

CGame::CGame()
{
}

CGame::~CGame()
{
	//for (auto it = vecBullets.begin(); it != vecBullets.end(); it++)
	//{
	//	delete (*it);
	//}
}

void CGame::Initialise()
{
	srand((unsigned int)time(0));
	previousTimeStamp = (float)glutGet(GLUT_ELAPSED_TIME);

	/*m_player = CPlayer();
	m_player.Initialise(0.0f, 0.0f, 0.0f, 0.2f, 90.0f, &m_camera);
	m_player.setModel();*/
	//m_player.setAngle(90.0f);
	m_camera.Initialise(PERSPECTIVE);
	m_canvas.Initialise(ORTHOGRAPHIC);
	//m_audio.Initialise();

	// LOAD TEXT
	//scoreText = new TextLabel("Score: ", "Resources/Fonts/arial.ttf", glm::vec2(-400.0f, 375.0f));
	//healthText = new TextLabel("Health: ", "Resources/Fonts/arial.ttf", glm::vec2(250.0f, 375.0f));
	//scoreText->SetScale(0.5f);
	//healthText->SetScale(0.5f);

	//menuStart = new TextLabel("Start Game ", "Resources/Fonts/arial.ttf", glm::vec2(-150.0f, 300.0f));
	//menuExit = new TextLabel("Exit Game ", "Resources/Fonts/arial.ttf", glm::vec2(-150.0f, 100.0f));

	// LOAD AUDIO

	// LOAD PROGRAMS
	m_PROGRAMS["SIMPLE"] = ShaderLoader::CreateProgram("Resources/Shaders/simple.verts", "Resources/Shaders/simple.frags");
	m_PROGRAMS["SIMPLE_BLINN"] = ShaderLoader::CreateProgram("Resources/Shaders/simpleBlinnPhong.verts", "Resources/Shaders/simpleBlinnPhong.frags");
	m_PROGRAMS["SIMPLE_RIM"] = ShaderLoader::CreateProgram("Resources/Shaders/simpleRim.verts", "Resources/Shaders/simpleRim.frags");
	m_PROGRAMS["SPHERE_BLINN"] = ShaderLoader::CreateProgram("Resources/Shaders/sphereBlinnPhong.verts", "Resources/Shaders/sphereBlinnPhong.frags");
	m_PROGRAMS["SPHERE_RIM"] = ShaderLoader::CreateProgram("Resources/Shaders/sphereRim.verts", "Resources/Shaders/sphereRim.frags");
	m_PROGRAMS["SPHERE_RIMBLUE"] = ShaderLoader::CreateProgram("Resources/Shaders/sphereRimBlue.verts", "Resources/Shaders/sphereRimBlue.frags");
	m_PROGRAMS["SPHERE_REFLECT"] = ShaderLoader::CreateProgram("Resources/Shaders/reflectiveSphere.verts", "Resources/Shaders/reflectiveSphere.frags");
	m_PROGRAMS["CUBEMAP"] = ShaderLoader::CreateProgram("Resources/Shaders/cubeMap.verts", "Resources/Shaders/cubeMap.frags");
	m_PROGRAMS["MODEL"] = ShaderLoader::CreateProgram("Resources/Shaders/model.verts", "Resources/Shaders/model.frags");
	m_PROGRAMS["TEXT"] = ShaderLoader::CreateProgram("Resources/Shaders/text.verts", "Resources/Shaders/text.frags");
	m_PROGRAMS["STENCIL"] = ShaderLoader::CreateProgram("Resources/Shaders/simple.verts", "Resources/Shaders/stencil.frags");
	m_PROGRAMS["FOG"] = ShaderLoader::CreateProgram("Resources/Shaders/simpleBlinnPhong.verts", "Resources/Shaders/simpleBlinnPhongFOG.frags");
	m_PROGRAMS["HEIGHTMAP"] = ShaderLoader::CreateProgram("Resources/Shaders/heightmap.verts", "Resources/Shaders/heightmap.frags");
	//m_PROGRAMS["TEST"] = ShaderLoader::CreateProgram("Resources/Shaders/test.verts", "Resources/Shaders/test.frags");
	m_PROGRAMS["GEOMETRY"] = ShaderLoader::CreateProgram("Resources/Shaders/geometry.verts", "Resources/Shaders/geometry.frags", "Resources/Shaders/geometry.geoms");
	m_PROGRAMS["TESSELATION"] = ShaderLoader::CreateProgram(
		"Resources/Shaders/tesselation.verts",
		"Resources/Shaders/tesselation.frags",
		"Resources/Shaders/tesselation.tcs",
		"Resources/Shaders/tesselation.tes");

	// LOAD TEXTURES
	m_TEXTURES["RAYMAN"] = Utils::loadTexture("Resources/Textures/Rayman.jpg");
	m_TEXTURES["UNIMPRESSED"] = Utils::loadTexture("Resources/Textures/unimpressed.png");
	m_TEXTURES["AWESOME"] = Utils::loadTexture("Resources/Textures/AwesomeFace.png");
	m_TEXTURES["GRID"] = Utils::loadTexture("Resources/Textures/grid.jpg");
	m_TEXTURES["WATER"] = Utils::loadTexture("Resources/Textures/WaterTex.png");

	//m_audio.playSound("BACKGROUND");

	//m_reflectiveSphere.initialise(m_PROGRAMS["SPHERE_REFLECT"], m_TEXTURES["RAYMAN"], 0.0f, 0.0f, 1.0f);
	////m_floor = CQuad();
	//m_floor.initialise(m_PROGRAMS["FOG"], m_TEXTURES["RAYMAN"], 0.0f, 0.0f, 5.0f);
	//m_floor.setRotX(-90.0f);
	//m_floor.setRotZ(45.0f);
	//m_water.initialise(m_PROGRAMS["FOG"], m_TEXTURES["WATER"], 0.0f, 0.1f, 5.0f);
	////testQuad.setPosZ(-0.01f)
	//m_water.setRotX(-90.0f);
	//m_water.setRotZ(45.0f);
	//m_cubeMap = CCubeMap(&m_camera);
	//testCube.initialise(m_PROGRAMS["FOG"], m_TEXTURES["UNIMPRESSED"], 0.0f, 0.0f, 0.0f, 1.0f);
	//testCube.setRotX(30.0f);
	//testCube.setRotY(50.0f);
	//testCube.setRotZ(70.0f);

	//zoomIn.initialise(m_PROGRAMS["SIMPLE"], m_TEXTURES["AWESOME"], -300.0f, 0.0f, 0.0f, 100.0f);
	//zoomOut.initialise(m_PROGRAMS["SIMPLE"], m_TEXTURES["AWESOME"], 300.0f, 0.0f, 0.0f, 100.0f);


	//m_stencilCube.initialise(m_PROGRAMS["STENCIL"], m_TEXTURES["UNIMPRESSED"], 0.0f, 0.0f, 0.0f, 5.0f);

	// create heightmap
	//m_terrain = Terrain();
	m_terrain.initialise(m_PROGRAMS["HEIGHTMAP"], m_TEXTURES["RAYMAN"], 0.0f, 0.0f, 0.0f, 1.0f);

	m_star = GeometryModel(m_PROGRAMS["GEOMETRY"]);
	m_star.setPosX(6.0f);
	m_star.setPosY(60.0f);
	m_star.setPosZ(0.0f);
	m_star.setScaleX(20.0f);
	m_star.setScaleY(20.0f);
	m_star.setScaleZ(20.0f);

	m_tesselatedModel = TessModel(m_PROGRAMS["TESSELATION"]);
	m_tesselatedModel.setPosX(6.0f);
	m_tesselatedModel.setPosY(60.0f);
	m_tesselatedModel.setPosZ(0.0f);
	m_tesselatedModel.setScaleX(20.0f);
	m_tesselatedModel.setScaleY(20.0f);
	m_tesselatedModel.setScaleZ(20.0f);

	m_camera.setCameraSpeed(200.0f);
}

void CGame::Render()
{
	//glEnable(GL_CULL_FACE);

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//glPolygonMode(GL_FRONT, GL_LINE);
	
	
	//m_cubeMap.Render();
	//m_reflectiveSphere.Render(&m_camera, m_cubeMap.getTexID());
	//m_floor.Render(&m_camera);
	//m_water.Render(&m_camera);

	m_terrain.Render(&m_camera);
	m_star.Render(&m_camera);
	m_tesselatedModel.Render(&m_camera);

	//// Stencil Buffer
	//glEnable(GL_STENCIL_TEST);
	//glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE); // stfail, dpFail, bothPass
	//glStencilFunc(GL_ALWAYS, 1, 0xFF); // specify condition for stencil pass
	//glStencilMask(0xFF); // enable writing to stencil buffer
	//testCube.Render(&m_camera);
	//glStencilMask(0x00); // disable writing to stencil buffer
	//glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	//DrawScaledUp(&testCube, 1.1f); // draw scaled up object
	//glDisable(GL_STENCIL_TEST);
	//glStencilMask(0xFF); // enable writing to stencil buffer

	//glDisable(GL_DEPTH);

	//zoomIn.Render(&m_canvas);
	//zoomOut.Render(&m_canvas);

	//glEnable(GL_DEPTH);

	/*glDisable(GL_SCISSOR_TEST);*/
	//glDisable(GL_CULL_FACE);
	/*glEnable(GL_DEPTH_TEST);*/
}

void CGame::Update()
{
	ProcessDeltaTime();
	
	//m_cubeMap.Update();
	m_camera.Update(deltaTime);

	if (m_inputController.KeyState['w'] == INPUT_DOWN)
	{
		m_camera.moveForward(deltaTime);
	}

	if (m_inputController.KeyState['s'] == INPUT_DOWN)
	{
		m_camera.moveBack(deltaTime);
	}

	if (m_inputController.KeyState['a'] == INPUT_DOWN)
	{
		m_camera.moveLeft(deltaTime);
	}

	if (m_inputController.KeyState['d'] == INPUT_DOWN)
	{
		m_camera.moveRight(deltaTime);
	}

	if (m_inputController.KeyState['r'] == INPUT_DOWN_FIRST)
	{
		ResetGame();
	}

	// Camera follow heightmap

	// make sure the camera is within the bounds of the heightmap before checking for height
	if (!(m_camera.getCamPos().x >= m_terrain.width()* 0.5 || m_camera.getCamPos().x <= m_terrain.width()* -0.5 ||
		m_camera.getCamPos().z >= m_terrain.depth()* 0.5 || m_camera.getCamPos().z <= m_terrain.depth()* -0.5))
	{
		m_camera.setCamPos(glm::vec3(m_camera.getCamPos().x, m_terrain.getHeight(m_camera.getCamPos().x, m_camera.getCamPos().z) + 20.0f, m_camera.getCamPos().z));
	}


	mouseX = m_inputController.getMouseXWindow();
	mouseY = m_inputController.getMouseYWindow();

	//testCube.setPosX(m_camera.getCamPos().x);
	//testCube.setPosY(m_camera.getCamPos().y);
	//testCube.setPosZ(m_camera.getCamPos().z + 5.0f);

	//bool test = UpdateMousePicking(&zoomIn) && m_inputController.MouseState[0] == INPUT_DOWN_FIRST;

	//std::cout << "CLICKING LEFT " + test << std::endl;

	m_inputController.ProcessInput();
}



float CGame::getDeltaTime()
{
	return deltaTime;
}


void CGame::ResetGame()
{
	m_camera.ResetCamera();
}

void CGame::ProcessDeltaTime()
{
	// process deltaTime
	float currentTime = (float)glutGet(GLUT_ELAPSED_TIME);
	deltaTime = (currentTime - previousTimeStamp) * 0.001f;
	previousTimeStamp = currentTime;



	//std::cout << "DeltaTime = " << deltaTime << std::endl;
	elapsedTime += deltaTime;
	if (deltaTime >= 1.0f)
	{
		deltaTime = 1.0f;
	}
}

//void CGame::DrawScaledUp(CShape* _object, float _scale)
//{
//	//// scale up
//	//_object->setScaleX(_object->getScaleX() * _scale);
//	//_object->setScaleY(_object->getScaleY() * _scale);
//	//_object->setScaleZ(_object->getScaleZ() * _scale);
//
//	// get the cubes info
//	m_stencilCube.setScaleX(_object->getScaleX() * _scale);
//	m_stencilCube.setScaleY(_object->getScaleY() * _scale);
//	m_stencilCube.setScaleZ(_object->getScaleZ() * _scale);
//
//	m_stencilCube.setRotX(_object->getRotX());
//	m_stencilCube.setRotY(_object->getRotY());
//	m_stencilCube.setRotZ(_object->getRotZ());
//
//	m_stencilCube.setPosX(_object->getPosX());
//	m_stencilCube.setPosY(_object->getPosY());
//	m_stencilCube.setPosZ(_object->getPosZ());
//
//
//}

bool CGame::UpdateMousePicking(CShape* _object)
{
	// screen pos
	glm::vec2 normalizedScreenPos = glm::vec2(mouseX, mouseY);

	// screenpos to Proj Space
	glm::vec4 clipCoords = glm::vec4(normalizedScreenPos.x, normalizedScreenPos.y, -1.0f, 1.0f);

	// Proj Space to eye space
	glm::mat4 invProjMat = glm::inverse(m_canvas.getProjMat());
	glm::vec4 eyeCoords = invProjMat * clipCoords;
	eyeCoords = glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);

	// eyespace to world space
	glm::mat4 invViewMat = glm::inverse(m_canvas.getViewMat());
	glm::vec4 rayWorld = invViewMat * eyeCoords;
	rayDirection = glm::normalize(glm::vec3(rayWorld));

	// code to check intersection with other objects
	// SPHERE
	//float radius = _object->getScaleX();
	//glm::vec3 v = glm::vec3(_object->getPosX(), _object->getPosY(), _object->getPosZ()) - m_canvas.getCamPos();

	//float a = glm::dot(rayDirection, rayDirection);
	//float b = 2 * glm::dot(v, rayDirection);
	//float c = glm::dot(v, v) - radius * radius;
	//float d = b * b - 4 * a*c;

	//if (d > 0)
	//{
	//	float x1 = (-b - sqrt(d)) / 2;
	//	float x2 = (-b + sqrt(d)) / 2;
	//	if (x1 >= 0 && x2 >= 0) return true; // intersects
	//	if (x1 < 0 && x2 >= 0) return true; // intersects
	//}
	//else if (d <= 0)
	//{
	//	return false; // no intersection
	//}

	// CUBE
	float tmin = ((_object->getPosX() - _object->getScaleX()) - m_canvas.getCamPos().x) / rayDirection.x;
	float tmax = ((_object->getPosX() + _object->getScaleX()) - m_canvas.getCamPos().x) / rayDirection.x;

	if (tmin > tmax) swap(tmin, tmax);

	float tymin = ((_object->getPosY() - _object->getScaleY()) - m_canvas.getCamPos().y) / rayDirection.y;
	float tymax = ((_object->getPosY() + _object->getScaleY()) - m_canvas.getCamPos().y) / rayDirection.y;

	if (tymin > tymax) swap(tymin, tymax);

	if ((tmin > tymax) || (tymin > tmax))
		return false;

	if (tymin > tmin)
		tmin = tymin;

	if (tymax < tmax)
		tmax = tymax;

	float tzmin = ((_object->getPosZ() - _object->getScaleZ()) - m_canvas.getCamPos().z) / rayDirection.z;
	float tzmax = ((_object->getPosZ() + _object->getScaleZ()) - m_canvas.getCamPos().z) / rayDirection.z;

	if (tzmin > tzmax) swap(tzmin, tzmax);

	if ((tmin > tzmax) || (tzmin > tmax))
		return false;

	/*if (tzmin > tmin)
		tmin = tzmin;

	if (tzmax < tmax)
		tmax = tzmax;*/

	return true;
}



