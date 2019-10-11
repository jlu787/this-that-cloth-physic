#include "pyramid.h"


//void CPyramid::initialise(const char * file, int _x, int _y, float _scale)
//{
//	// load in the program
//	m_program = ShaderLoader::CreateProgram("Resources/Shaders/simpleBlinnPhong.verts",
//		"Resources/Shaders/simpleBlinnPhong.frags");
//
//	m_posX = (float)_x;
//	m_posY = (float)_y;
//	m_posZ = 0.0f;
//
//	m_scaleX = _scale;
//	m_scaleY = _scale;
//	m_scaleZ = _scale;
//
//	// VAO
//	glGenVertexArrays(1, &m_VAO);
//	glBindVertexArray(m_VAO);
//
//	// EBO
//	glGenBuffers(1, &m_EBO);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//	// VBO
//	glGenBuffers(1, &m_VBO);
//	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	// Texture
//	glGenTextures(1, &m_tex);
//	glBindTexture(GL_TEXTURE_2D, m_tex);
//
//	int width, height;
//	unsigned char* image = SOIL_load_image(file, &width, &height, 0, SOIL_LOAD_RGBA); // Load Image
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);	// Create texture with the loaded data
//
//	glGenerateMipmap(GL_TEXTURE_2D);	// Generate Mipmap
//	SOIL_free_image_data(image);		// Free memory
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//
//	glBindTexture(GL_TEXTURE_2D, 0);	// Unbind texture
//
//	glVertexAttribPointer(
//		0,
//		3,
//		GL_FLOAT,
//		GL_FALSE,
//		11 * sizeof(GLfloat),	// Stride of the single vertex (pos)
//		(GLvoid*)0);			// Offset from beginning of Vertex
//	glEnableVertexAttribArray(0);
//
//	// Sending color data
//	glVertexAttribPointer(
//		1,
//		3,
//		GL_FLOAT,
//		GL_FALSE,
//		11 * sizeof(GLfloat),	// Stride of the single vertex (pos)
//		(GLvoid*)(3 * sizeof(GLfloat)));			// Offset from beginning of Vertex
//	glEnableVertexAttribArray(1);
//
//	// Sending texture data
//	glVertexAttribPointer(
//		2,
//		2,									// 2 floats for texture coordinates
//		GL_FLOAT,
//		GL_FALSE,
//		11 * sizeof(GLfloat),
//		(GLvoid*)(6 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(2);
//
//	// Sending texture data
//	glVertexAttribPointer(
//		3,
//		3,									// 3 floats for normals
//		GL_FLOAT,
//		GL_FALSE,
//		11 * sizeof(GLfloat),
//		(GLvoid*)(8 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(3);
//}

void CPyramid::initialise(GLuint _program, GLuint _texture, int _x, int _y, float _scale)
{
	// load in the program
	m_program = _program;
	m_tex = _texture;

	m_posX = (float)_x;
	m_posY = (float)_y;
	m_posZ = 0.0f;

	m_scaleX = _scale;
	m_scaleY = _scale;
	m_scaleZ = _scale;

	// VAO
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	// EBO
	glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// VBO
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//// Texture
	//glGenTextures(1, &m_tex);
	//glBindTexture(GL_TEXTURE_2D, m_tex);

	//int width, height;
	//unsigned char* image = SOIL_load_image(file, &width, &height, 0, SOIL_LOAD_RGBA); // Load Image
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);	// Create texture with the loaded data

	//glGenerateMipmap(GL_TEXTURE_2D);	// Generate Mipmap
	//SOIL_free_image_data(image);		// Free memory

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//glBindTexture(GL_TEXTURE_2D, 0);	// Unbind texture

	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		11 * sizeof(GLfloat),	// Stride of the single vertex (pos)
		(GLvoid*)0);			// Offset from beginning of Vertex
	glEnableVertexAttribArray(0);

	// Sending color data
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		11 * sizeof(GLfloat),	// Stride of the single vertex (pos)
		(GLvoid*)(3 * sizeof(GLfloat)));			// Offset from beginning of Vertex
	glEnableVertexAttribArray(1);

	// Sending texture data
	glVertexAttribPointer(
		2,
		2,									// 2 floats for texture coordinates
		GL_FLOAT,
		GL_FALSE,
		11 * sizeof(GLfloat),
		(GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	// Sending texture data
	glVertexAttribPointer(
		3,
		3,									// 3 floats for normals
		GL_FLOAT,
		GL_FALSE,
		11 * sizeof(GLfloat),
		(GLvoid*)(8 * sizeof(GLfloat)));
	glEnableVertexAttribArray(3);
}

void CPyramid::Render(CCamera * _gameCam)
{
	glUseProgram(m_program);

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Translation

	glm::vec3 objPosition = glm::vec3(m_posX, m_posY, m_posZ); // This is how much you will translate by
	glm::mat4 translationMatrix = glm::translate(glm::mat4(), objPosition); // create the transformation matrix

																			// Rotation
	glm::vec3 rotationAxisZ = glm::vec3(0.0f, 0.0f, 1.0f);
	float rotationAngle = 0;
	glm::mat4 rotationZ = glm::rotate(glm::mat4(), glm::radians(rotationAngle), rotationAxisZ);

	// Scaling
	glm::vec3 objScale = glm::vec3(m_scaleX, m_scaleY, m_scaleZ);
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(), objScale);

	// Getting model matrix
	glm::mat4 model = translationMatrix * rotationZ * scaleMatrix;

	// Send model matrix
	GLuint modelLoc = glGetUniformLocation(m_program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	// MVP Matrix
	// Calculate the MVP matrix
	glm::mat4 MVP = _gameCam->getProjMat() * _gameCam->getViewMat() * model;
	// Send via uniform
	GLuint projLoc = glGetUniformLocation(m_program, "mvp");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(MVP));

	// Send cam pos
	GLuint camLoc = glGetUniformLocation(m_program, "camPos");
	glUniform3fv(camLoc, 1, glm::value_ptr(_gameCam->getCamPos()));

	// Bind Texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_tex);
	glUniform1i(glGetUniformLocation(m_program, "tex"), 0);

	glBindVertexArray(m_VAO);	// Bind VAO
	glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0); // Unbind VAO

	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
