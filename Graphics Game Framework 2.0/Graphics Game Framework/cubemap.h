#pragma once
#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <vector>
#include "camera.h"
#include "ShaderLoader_Complete.h"



class CCubeMap
{
public:
	CCubeMap();
	//CCubeMap(CCamera* _gameCam, std::vector<const char*> _filePaths);
	CCubeMap(CCamera* _gameCam);

	~CCubeMap();

	void Update();
	void Render();

	unsigned int getTexID() {return textureID;};
private:
	GLuint m_program, m_VAO, m_EBO, m_VBO;
	CCamera* m_camera;
	unsigned int textureID;
	glm::mat4 MVP;

	// vertices for a basic cube
	GLfloat vertices[24 * 3]{
		// Positions			
		// Front
		-0.5f,  0.5f,  0.5f,	// 0
		-0.5f, -0.5f,  0.5f,	// 1
		 0.5f, -0.5f,  0.5f,	// 2
		 0.5f,  0.5f,  0.5f,	// 3

		// Back
		-0.5f,  0.5f, -0.5f,	// 4
		-0.5f, -0.5f, -0.5f,	// 5
		 0.5f, -0.5f, -0.5f,	// 6
		 0.5f,  0.5f, -0.5f,	// 7

		// Left
		-0.5f,  0.5f, -0.5f,	// 8
		-0.5f, -0.5f, -0.5f,	// 9
		-0.5f, -0.5f,  0.5f,	// 10
		-0.5f,  0.5f,  0.5f,	// 11

		// Right
		 0.5f,	0.5f,  0.5f,	// 12
		 0.5f, -0.5f,  0.5f,	// 13
		 0.5f, -0.5f, -0.5f,	// 14
		 0.5f,	0.5f, -0.5f,	// 15

		 // Top
		-0.5f,  0.5f, -0.5f,	// 16
		-0.5f,  0.5f,  0.5f,	// 17
		 0.5f,  0.5f,  0.5f,	// 18
		 0.5f,  0.5f, -0.5f,	// 19

		 // Bottom
		 -0.5f, -0.5f,  0.5f,	// 20
		 -0.5f, -0.5f, -0.5f,	// 21
		  0.5f, -0.5f, -0.5f,	// 22
		  0.5f, -0.5f,  0.5f,	// 23
	};

	//// normal
	//GLuint indices[36] = {
	//	0,  1,  2, // Front
	//	0,  2,  3, // Front

	//	7,  6,  5, // Back
	//	7,  5,  4, // Back

	//	8,  9, 10, // Left
	//	8, 10, 11, // Left

	//	12, 13, 14, // Right
	//	12, 14, 15, // Right

	//	16, 17, 18, // Top
	//	16, 18, 19, // Top

	//	20, 21, 22, // Bottom
	//	20, 22, 23, // Bottom
	//};

	// reversed
	GLuint indices[36] = {
		2,  1,  0, // Front
		3,  2,  0, // Front

		5,  6,  7, // Back
		4,  5,  7, // Back

		10,  9, 8, // Left
		11, 10, 8, // Left

		14, 13, 12, // Right
		15, 14, 12, // Right

		18, 17, 16, // Top
		19, 18, 16, // Top

		22, 21, 20, // Bottom
		23, 22, 20, // Bottom
	};

	

	std::vector<std::string> faces
	{
		"right.jpg",
		"left.jpg",
		"top.jpg",
		"bottom.jpg",
		"back.jpg",
		"front.jpg",
	};
};
