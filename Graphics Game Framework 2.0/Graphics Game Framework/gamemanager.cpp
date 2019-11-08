#include "gamemanager.h"

CGame::CGame()
{
	//m_cloth = CCloth(0,0,0,0,0,0,0);
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
	//m_PROGRAMS["SIMPLE_BLINN"] = ShaderLoader::CreateProgram("Resources/Shaders/simpleBlinnPhong.verts", "Resources/Shaders/simpleBlinnPhong.frags");
	//m_PROGRAMS["SIMPLE_RIM"] = ShaderLoader::CreateProgram("Resources/Shaders/simpleRim.verts", "Resources/Shaders/simpleRim.frags");
	//m_PROGRAMS["SPHERE_BLINN"] = ShaderLoader::CreateProgram("Resources/Shaders/sphereBlinnPhong.verts", "Resources/Shaders/sphereBlinnPhong.frags");
	//m_PROGRAMS["SPHERE_RIM"] = ShaderLoader::CreateProgram("Resources/Shaders/sphereRim.verts", "Resources/Shaders/sphereRim.frags");
	//m_PROGRAMS["SPHERE_RIMBLUE"] = ShaderLoader::CreateProgram("Resources/Shaders/sphereRimBlue.verts", "Resources/Shaders/sphereRimBlue.frags");
	m_PROGRAMS["SPHERE_REFLECT"] = ShaderLoader::CreateProgram("Resources/Shaders/reflectiveSphere.verts", "Resources/Shaders/reflectiveSphere.frags");
	//m_PROGRAMS["CUBEMAP"] = ShaderLoader::CreateProgram("Resources/Shaders/cubeMap.verts", "Resources/Shaders/cubeMap.frags");
	//m_PROGRAMS["MODEL"] = ShaderLoader::CreateProgram("Resources/Shaders/model.verts", "Resources/Shaders/model.frags");
	//m_PROGRAMS["TEXT"] = ShaderLoader::CreateProgram("Resources/Shaders/text.verts", "Resources/Shaders/text.frags");
	//m_PROGRAMS["STENCIL"] = ShaderLoader::CreateProgram("Resources/Shaders/simple.verts", "Resources/Shaders/stencil.frags");
	//m_PROGRAMS["FOG"] = ShaderLoader::CreateProgram("Resources/Shaders/simpleBlinnPhong.verts", "Resources/Shaders/simpleBlinnPhongFOG.frags");
	//m_PROGRAMS["HEIGHTMAP"] = ShaderLoader::CreateProgram("Resources/Shaders/heightmap.verts", "Resources/Shaders/heightmap.frags");
	////m_PROGRAMS["TEST"] = ShaderLoader::CreateProgram("Resources/Shaders/test.verts", "Resources/Shaders/test.frags");
	//m_PROGRAMS["GEOMETRY"] = ShaderLoader::CreateProgram("Resources/Shaders/geometry.verts", "Resources/Shaders/geometry.frags", "Resources/Shaders/geometry.geoms");
	//m_PROGRAMS["TESSELATION"] = ShaderLoader::CreateProgram(
	//	"Resources/Shaders/tesselation.verts",
	//	"Resources/Shaders/tesselation.frags",
	//	"Resources/Shaders/tesselation.tcs",
	//	"Resources/Shaders/tesselation.tes");
	m_PROGRAMS["SPHERE_COLOR"] = ShaderLoader::CreateProgram("Resources/Shaders/sphereBlinnPhong.verts", "Resources/Shaders/sphereColor.frags");
	//m_PROGRAMS["LINE"] = ShaderLoader::CreateProgram("Resources/Shaders/line.verts", "Resources/Shaders/line.frags");
	m_PROGRAMS["LINE"] = ShaderLoader::CreateProgram("Resources/Shaders/newLine.verts", "Resources/Shaders/newLine.frags",	"Resources/Shaders/newLine.geoms");


	// LOAD TEXTURES
	m_TEXTURES["RAYMAN"] = Utils::loadTexture("Resources/Textures/Rayman.jpg");
	m_TEXTURES["FAN"] = Utils::loadTexture("Resources/Textures/fan.jpg");

	sphere.initialise(m_PROGRAMS["SPHERE_COLOR"], m_TEXTURES["RAYMAN"], 10, 10, 4.0f);
	fan.initialise(m_PROGRAMS["SIMPLE"], m_TEXTURES["FAN"], 0, 0, 0, 2.0f);

	m_cubeMap = CCubeMap(&m_camera);

	m_cloth = new CCloth(cloth_width, cloth_height, cloth_points_width, cloth_points_height, m_PROGRAMS["LINE"], m_PROGRAMS["SPHERE_COLOR"], m_TEXTURES["RAYMAN"]);

	m_camera.setCameraSpeed(200.0f);
}

void CGame::Render()
{
	//glEnable(GL_CULL_FACE);

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//glPolygonMode(GL_FRONT, GL_LINE);

	m_cloth->addForce(glm::vec3(0, -0.2, 0)*(float)(TIME_STEP)); // add gravity each frame

	if (!fanActive) // Global wind force if fan is not active.
	{
		m_cloth->windForce(windSpeed*(float)(TIME_STEP)); // generate some wind each frame
	}
	else
	{
		fan.Render(&m_camera);
	}

	m_cloth->timeStep(); // calculate the point positions of the next frame	
	m_cloth->GroundCheck();
	
	m_cubeMap.Render();
	sphere.Render(&m_camera);
	
	m_cloth->Render(&m_camera);
}

void CGame::Update()
{
	ProcessDeltaTime();
	
	m_cubeMap.Update();
	m_camera.Update(deltaTime);
	//m_cloth->Update(deltaTime);

	// MOVING CAMERA
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

	// RESETTING GAME
	if (m_inputController.KeyState['r'] == INPUT_DOWN_FIRST)
	{
		ResetGame();
	}

	// RELEASING
	if (m_inputController.KeyState['1'] == INPUT_DOWN_FIRST)
	{
		m_cloth->Release();

	}

	// SLIDING RINGS
	if (m_inputController.KeyState['j'] == INPUT_DOWN)
	{
		m_cloth->SlideRings(-0.5);
	}
	
	if (m_inputController.KeyState['k'] == INPUT_DOWN)
	{
		m_cloth->SlideRings(0.5);
	}

	// SWITCHING IF THE CLOTH CAN BE TORN OR NOT
	if (m_inputController.KeyState['u'] == INPUT_DOWN_FIRST)
	{
		m_cloth->canBeTorn = !m_cloth->canBeTorn;
	}

	// ADDING POINTS VERTICALLY
	if (m_inputController.KeyState['o'] == INPUT_DOWN_FIRST)
	{
		cloth_height++;
		cloth_points_height++;
		ResetGame();
	}

	// ADDING POINTS HORIZONTALLY
	if (m_inputController.KeyState['p'] == INPUT_DOWN_FIRST)
	{
		cloth_width++;
		cloth_points_width++;
		ResetGame();
	}

	// REMOVING POINTS VERTICALLY
	if (m_inputController.KeyState['l'] == INPUT_DOWN_FIRST)
	{
		if (cloth_height > min_height)
		{
			cloth_height--;
			cloth_points_height--;
			ResetGame();
		}
	}

	// REMOVING POINTS HORIZONTALLY
	if (m_inputController.KeyState[';'] == INPUT_DOWN_FIRST)
	{
		if (cloth_width > min_width)
		{
			cloth_width--;
			cloth_points_width--;
			ResetGame();
		}
	}

	// MOVING THE SPHERE UP
	if (m_inputController.KeyState['8'] == INPUT_DOWN)
	{
		sphere.setPosY(sphere.getPosY() + 20.0f * deltaTime);
	}

	// MOVING THE SPHERE DOWN
	if (m_inputController.KeyState['2'] == INPUT_DOWN)
	{
		sphere.setPosY(sphere.getPosY() - 20.0f * deltaTime);
	}

	// MOVING THE SPHERE RIGHT
	if (m_inputController.KeyState['6'] == INPUT_DOWN)
	{
		sphere.setPosX(sphere.getPosX() + 20.0f * deltaTime);
	}

	// MOVING THE SPHERE LEFT
	if (m_inputController.KeyState['4'] == INPUT_DOWN)
	{
		sphere.setPosX(sphere.getPosX() - 20.0f * deltaTime);
	}

	// MOVING THE SPHERE FORWARD
	if (m_inputController.KeyState['7'] == INPUT_DOWN)
	{
		sphere.setPosZ(sphere.getPosZ() - 20.0f * deltaTime);
	}

	// MOVING THE SPHERE BACK
	if (m_inputController.KeyState['9'] == INPUT_DOWN)
	{
		sphere.setPosZ(sphere.getPosZ() + 20.0f * deltaTime);
	}

	// TOGGLING THE FAN ON AND OFF
	if (m_inputController.KeyState['i'] == INPUT_DOWN_FIRST)
	{
		fanActive = !fanActive;
	}

	// INCREASING WIND
	if (m_inputController.KeyState['n'] == INPUT_DOWN_FIRST)
	{
		windSpeed += glm::vec3(0.0f,0.0f,0.1f);
	}

	// TOGGLING THE FAN ON AND OFF
	if (m_inputController.KeyState['m'] == INPUT_DOWN_FIRST)
	{
		windSpeed -= glm::vec3(0.0f, 0.0f, 0.1f);
	}


	// TOGGLING TORCH ON AND OFF
	if (m_inputController.KeyState['z'] == INPUT_DOWN_FIRST)
	{
		torchOn = !torchOn;
	}

	// The escape key 
	if (m_inputController.KeyState[27] == INPUT_DOWN_FIRST)
	{
		ShutDown();
	}

	// PROCESSING THE COLLISION BETWEEN THE SPHERE AND CLOTH
	for (auto &point : m_cloth->points)
	{
		if (point.GetMovable())
		{
			float distance = glm::distance(point.getPos(), sphere.getPos());
			float radius = sphere.getScaleX();

			// check if colliding
			if (distance < radius)
			{
				point.setPos(sphere.getPos() + glm::normalize(point.getPos() - sphere.getPos())*(radius + 0.1f));
			}
		}
	}

	// PROCESSING THE WIND OF FAN
	if (fanActive)
	{
		for (auto &point : m_cloth->points)
		{
			// check if the point is inside the circle of wind projected by the fan

			float d2 = (point.getPos().x - fan.getPos().x) * (point.getPos().x - fan.getPos().x) +
				(point.getPos().y - fan.getPos().y) * (point.getPos().y - fan.getPos().y);

			float r2 = (float)(5.0f * 5.0f);
			if (d2 < r2)
			{
				//std::cout << "We are inside the fan range" << std::endl;
				//point.addForce({ 0.0f, 0.0f, -1.0f });

				m_cloth->addWindForceForPoint(point.x, point.y, { 0.0f, 0.0f, -0.1f });
			}
		}
	}
	

	mousePos = m_inputController.GetMouseNDC();
	/*std::cout << "MouseX = " << mouseX <<  std::endl;
	std::cout << "MouseY = " << mouseY <<  std::endl;*/

	
	//// test the gluUnproject
	//if (m_inputController.MouseState[0] == INPUT_DOWN)

	//	// *************** gluUNPROJECT************
	//{
	//	////glm::mat4 modelView = m_reflectiveSphere.getModelMatrix();

	//	//int viewport[4];
	//	//double modelView[16];
	//	//double projection[16];

	//	//double posX, posY, posZ;

	//	//glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
	//	//glGetDoublev(GL_PROJECTION_MATRIX, projection);
	//	//glGetIntegerv(GL_VIEWPORT, viewport);

	//	//glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
	//	//gluProject(m_inputController.GetMouseNDC().x, m_inputController.GetMouseNDC().y, 0.0, modelView, projection, viewport, &posX, &posY, &posZ);

	//	//m_reflectiveSphere.setPos(glm::vec3(posX, posY, posZ));

	//	// *************** PROJECTING NDC TO WORLD SPACE *************

	//	//// screen pos
	//	//glm::vec2 normalizedScreenPos = m_inputController.GetMouseNDC();

	//	//// screenpos to Proj Space
	//	//glm::vec4 clipCoords = glm::vec4(normalizedScreenPos.x, normalizedScreenPos.y, -1.0f, 1.0f);

	//	//// Proj Space to eye space
	//	//glm::mat4 invProjMat = glm::inverse(m_camera.getProjMat());
	//	//glm::vec4 eyeCoords = invProjMat * clipCoords;
	//	//eyeCoords = glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);

	//	//// eyespace to world space
	//	//glm::mat4 invViewMat = glm::inverse(m_camera.getViewMat());
	//	//glm::vec4 rayWorld = invViewMat * eyeCoords;
	//	////rayDirection = glm::normalize(glm::vec3(rayWorld));

	//	//glm::vec3 newPos = glm::vec3(eyeCoords);
	//	//newPos.z = 0;

	//	//m_reflectiveSphere.setPos(m_reflectiveSphere.getPos() + newPos);
	//	////m_reflectiveSphere.setPos(newPos);

	//	// ******************* PROJECTING DELTA NDC TO WORLD SPACE **************

	//		// screen pos
	//	glm::vec2 normalizedScreenPos = mousePos - mousePosLastFrame;

	//	// screenpos to Proj Space
	//	glm::vec4 clipCoords = glm::vec4(normalizedScreenPos.x, normalizedScreenPos.y, -1.0f, 1.0f);

	//	// Proj Space to eye space
	//	glm::mat4 invProjMat = glm::inverse(m_camera.getProjMat());
	//	glm::vec4 eyeCoords = invProjMat * clipCoords;
	//	eyeCoords = glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);

	//	// eyespace to world space
	//	glm::mat4 invViewMat = glm::inverse(m_camera.getViewMat());
	//	glm::vec4 rayWorld = invViewMat * eyeCoords;
	//	//rayDirection = glm::normalize(glm::vec3(rayWorld));

	//	glm::vec3 newPos = glm::vec3(rayWorld);
	//	newPos = glm::normalize(newPos) * glm::distance(m_reflectiveSphere.getPos(), m_camera.getCamPos());
	//	newPos.z = 0;

	//	m_reflectiveSphere.setPos(m_reflectiveSphere.getPos() + newPos);
	//	//m_reflectiveSphere.setPos(newPos);
	//}

	// check mouse picking on the fan
	if (m_inputController.MouseState[0] == INPUT_DOWN_FIRST && UpdateMousePicking(&fan) && fanActive)
	{
		//std::cout << "OOH YOU TOUCHIE TOUCHIE" << std::endl;
		fanBeingDragged = true;
	}

	if (fanBeingDragged)
	{
		DragObject(&fan);
	}
	//check mouse picking on cloth points if the fan is not already being dragged
	else
	{
		for (auto it = m_cloth->points.begin(); it != m_cloth->points.end(); it++)
		{
			if (UpdateMousePicking(&(*it).m_sphere) == true && m_inputController.MouseState[0] == INPUT_DOWN_FIRST)
			{
				//std::cout << "OOH YOU TOUCHIE TOUCHIE" << std::endl;
				(*it).beingDragged = true;

				if (torchOn)
				{
					(*it).onFire = true;
				}
				//if (m_inputController.MouseState[0] == INPUT_DOWN)
			}

			if ((*it).beingDragged)
			{
				DragObject(&(*it).m_sphere);
				(*it).setPos((*it).m_sphere.getPos());
			}
		}
	}


	// reset all points to not being dragged if mouse is up
	if (m_inputController.MouseState[0] == INPUT_UP_FIRST)
	{
		for (auto &point : m_cloth->points)
		{
			if (point.beingDragged) point.beingDragged = false;
		}
		fanBeingDragged = false;
	}


	//if (m_inputController.MouseState[0] == INPUT_DOWN)
	//{
	//	DragObject(&m_cloth->points[1].m_sphere);

	//}


	//std::cout << "deltaX = " << (mousePos - mousePosLastFrame).x << std::endl;
	//std::cout << "deltaY = " << (mousePos - mousePosLastFrame).y << std::endl;

	//std::cout << "CLICKING LEFT " + test << std::endl;

	lastMouseX = mouseX;
	lastMouseY = mouseY;


	mousePosLastFrame = mousePos;
	m_inputController.ProcessInput();
}



float CGame::getDeltaTime()
{
	return deltaTime;
}


void CGame::ResetGame()
{
	m_camera.ResetCamera();
	windSpeed = glm::vec3(0.0f, 0.0f, -0.1f);
	fanActive = false;

	delete m_cloth;

	m_cloth = new CCloth(cloth_width, cloth_height, cloth_points_width, cloth_points_height, m_PROGRAMS["LINE"], m_PROGRAMS["SPHERE_COLOR"], m_TEXTURES["RAYMAN"]);
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

void CGame::ShutDown()
{
	delete m_cloth;
	exit(0);
}

bool CGame::UpdateMousePicking(CShape* _object)
{
	// screen pos
	glm::vec2 normalizedScreenPos = m_inputController.GetMouseNDC();
	
	// screenpos to Proj Space
	glm::vec4 clipCoords = glm::vec4(normalizedScreenPos.x, normalizedScreenPos.y, -1.0f, 1.0f);

	// Proj Space to eye space
	glm::mat4 invProjMat = glm::inverse(m_camera.getProjMat());
	glm::vec4 eyeCoords = invProjMat * clipCoords;
	eyeCoords = glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);

	// eyespace to world space
	glm::mat4 invViewMat = glm::inverse(m_camera.getViewMat());
	glm::vec4 rayWorld = invViewMat * eyeCoords;
	rayDirection = glm::normalize(glm::vec3(rayWorld));

	// code to check intersection with other objects
	// SPHERE
	//float radius = _object->getScaleX();
	float radius = 0.5f; // keep at 0.5 for now
	glm::vec3 v = _object->getPos() - m_camera.getCamPos();
	

	float a = glm::dot(rayDirection, rayDirection);
	float b = 2 * glm::dot(v, rayDirection);
	float c = glm::dot(v, v) - radius * radius;
	float d = b * b - 4 * a*c;

	if (d > 0)
	{
		float x1 = (-b - sqrt(d)) / 2;
		float x2 = (-b + sqrt(d)) / 2;
		if (x1 >= 0 && x2 >= 0) return true; // intersects
		if (x1 < 0 && x2 >= 0) return true; // intersects
	}
	else if (d <= 0)
	{
		return false; // no intersection
	}

	//// CUBE
	//float tmin = ((_object->getPosX() - _object->getScaleX()) - m_canvas.getCamPos().x) / rayDirection.x;
	//float tmax = ((_object->getPosX() + _object->getScaleX()) - m_canvas.getCamPos().x) / rayDirection.x;

	//if (tmin > tmax) swap(tmin, tmax);

	//float tymin = ((_object->getPosY() - _object->getScaleY()) - m_canvas.getCamPos().y) / rayDirection.y;
	//float tymax = ((_object->getPosY() + _object->getScaleY()) - m_canvas.getCamPos().y) / rayDirection.y;

	//if (tymin > tymax) swap(tymin, tymax);

	//if ((tmin > tymax) || (tymin > tmax))
	//	return false;

	//if (tymin > tmin)
	//	tmin = tymin;

	//if (tymax < tmax)
	//	tmax = tymax;

	//float tzmin = ((_object->getPosZ() - _object->getScaleZ()) - m_canvas.getCamPos().z) / rayDirection.z;
	//float tzmax = ((_object->getPosZ() + _object->getScaleZ()) - m_canvas.getCamPos().z) / rayDirection.z;

	//if (tzmin > tzmax) swap(tzmin, tzmax);

	//if ((tmin > tzmax) || (tzmin > tmax))
	//	return false;

	return true;
}

void CGame::DragObject(CShape* _object)
{
	// screen pos
	glm::vec2 normalizedScreenPos = mousePos - mousePosLastFrame;

	// screenpos to Proj Space
	glm::vec4 clipCoords = glm::vec4(normalizedScreenPos.x, normalizedScreenPos.y, -1.0f, 1.0f);

	// Proj Space to eye space
	glm::mat4 invProjMat = glm::inverse(m_camera.getProjMat());
	glm::vec4 eyeCoords = invProjMat * clipCoords;
	eyeCoords = glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);

	// eyespace to world space
	glm::mat4 invViewMat = glm::inverse(m_camera.getViewMat());
	glm::vec4 rayWorld = invViewMat * eyeCoords;
	//rayDirection = glm::normalize(glm::vec3(rayWorld));

	glm::vec3 newPos = glm::vec3(rayWorld);
	newPos = glm::normalize(newPos) * glm::distance(_object->getPos(), m_camera.getCamPos());
	newPos.z = 0;

	_object->setPos(_object->getPos() + newPos);

	//std::cout << "newPos X = " << newPos.x << std::endl;
	//std::cout << "newPos Y = " << newPos.y << std::endl;
	//std::cout << "newPos Z = " << newPos.z << std::endl;

	//std::cout << "objPos X = " << _object->getPos().x << std::endl;
	//std::cout << "objPos Y = " << _object->getPos().y << std::endl;
	//std::cout << "objPos Z = " << _object->getPos().z << std::endl;
}



