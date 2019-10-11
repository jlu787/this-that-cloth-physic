#include "Sphere.h"

CSphere::CSphere()
{
	/*float radius = 1.0f;

	const int sections = 20;
	const int vertexAttrib = 8;
	const int indexPerQuad = 6;

	double phi = 0;
	double theta = 0;

	float vertices[(sections) * (sections) * vertexAttrib];
	int offset = 0;
	for (int i = 0; i < sections; i++)
	{
		theta = 0;

		for (int j = 0; j < sections; j++)
		{
			float x = cos(phi) * sin(theta);
			float y = cos(theta);
			float z = sin(phi) * sin(theta);

			vertices[offset++] = x * radius;
			vertices[offset++] = y * radius;
			vertices[offset++] = z * radius;
						   
			vertices[offset++] = x;
			vertices[offset++] = y;
			vertices[offset++] = z;
						   
			vertices[offset++] = (float)i / (sections - 1);
			vertices[offset++] = (float)j / (sections - 1);

			theta += (M_PI / (sections - 1));
		}

		phi += (2 * M_PI) / (sections - 1);
	}


	GLuint indices[(sections) * (sections) * indexPerQuad];
	offset = 0;
	for (int i = 0; i < sections; i++)
	{
		for (int j = 0; j < sections; j++)
		{
			indices[offset++] = (((i + 1) % sections) * sections) + ((j + 1) % sections);		
			indices[offset++] = (((i + 1) % sections) * sections) + (j);
			indices[offset++] = (i * sections) + (j);
						  
			indices[offset++] = (i * sections) + ((j + 1) % sections);
			indices[offset++] = (((i + 1) % sections) * sections) + ((j + 1) % sections);
			indices[offset++] = (i * sections) + (j);
		}
	}

	GLuint VBO, EBO;

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	IndiceCount = sizeof(indices) / sizeof(GLuint);
	DrawType = GL_TRIANGLES;*/
}



CSphere::~CSphere()
{
}

//void CSphere::initialise(const char * file, int _x, int _y, float _scale)
//{
//	// load in the program
//	m_program = ShaderLoader::CreateProgram("Resources/Shaders/sphereRim.verts",
//		"Resources/Shaders/sphereRim.frags");
//
//	m_posX = (float)_x;
//	m_posY = (float)_y;
//	m_posZ = 0.0f;
//
//	m_scaleX = _scale;
//	m_scaleY = _scale;
//	m_scaleZ = _scale;
//
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
//	float radius = 1.0f;
//
//	const int sections = 20;
//	const int vertexAttrib = 8;
//	const int indexPerQuad = 6;
//
//	double phi = 0;
//	double theta = 0;
//
//	float vertices[(sections) * (sections)* vertexAttrib];
//	int offset = 0;
//	for (int i = 0; i < sections; i++)
//	{
//		theta = 0;
//
//		for (int j = 0; j < sections; j++)
//		{
//			float x = cos(phi) * sin(theta);
//			float y = cos(theta);
//			float z = sin(phi) * sin(theta);
//
//			vertices[offset++] = x * radius;
//			vertices[offset++] = y * radius;
//			vertices[offset++] = z * radius;
//
//			vertices[offset++] = x;
//			vertices[offset++] = y;
//			vertices[offset++] = z;
//
//			vertices[offset++] = (float)i / (sections - 1);
//			vertices[offset++] = (float)j / (sections - 1);
//
//			theta += (M_PI / (sections - 1));
//		}
//
//		phi += (2 * M_PI) / (sections - 1);
//	}
//
//
//	GLuint indices[(sections) * (sections)* indexPerQuad];
//	offset = 0;
//	for (int i = 0; i < sections; i++)
//	{
//		for (int j = 0; j < sections; j++)
//		{
//			indices[offset++] = (((i + 1) % sections) * sections) + ((j + 1) % sections);
//			indices[offset++] = (((i + 1) % sections) * sections) + (j);
//			indices[offset++] = (i * sections) + (j);
//
//			indices[offset++] = (i * sections) + ((j + 1) % sections);
//			indices[offset++] = (((i + 1) % sections) * sections) + ((j + 1) % sections);
//			indices[offset++] = (i * sections) + (j);
//		}
//	}
//
//	GLuint VBO, EBO;
//
//	glGenVertexArrays(1, &m_VAO);
//	glBindVertexArray(m_VAO);
//
//	glGenBuffers(1, &VBO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	glGenBuffers(1, &EBO);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(1);
//
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(2);
//
//	IndiceCount = sizeof(indices) / sizeof(GLuint);
//	DrawType = GL_TRIANGLES;
//
//}

void CSphere::initialise(GLuint _program, GLuint _texture, int _x, int _y, float _scale)
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

	float radius = 1.0f;

	const int sections = 20;
	const int vertexAttrib = 8;
	const int indexPerQuad = 6;

	double phi = 0;
	double theta = 0;

	float vertices[(sections) * (sections)* vertexAttrib];
	int offset = 0;
	for (int i = 0; i < sections; i++)
	{
		theta = 0;

		for (int j = 0; j < sections; j++)
		{
			float x = (float)(cos(phi) * sin(theta));
			float y = (float)(cos(theta));
			float z = (float)(sin(phi) * sin(theta));

			vertices[offset++] = x * radius;
			vertices[offset++] = y * radius;
			vertices[offset++] = z * radius;

			vertices[offset++] = x;
			vertices[offset++] = y;
			vertices[offset++] = z;

			vertices[offset++] = (float)i / (sections - 1);
			vertices[offset++] = (float)j / (sections - 1);

			theta += (M_PI / (sections - 1));
		}

		phi += (2 * M_PI) / (sections - 1);
	}


	GLuint indices[(sections) * (sections)* indexPerQuad];
	offset = 0;
	for (int i = 0; i < sections; i++)
	{
		for (int j = 0; j < sections; j++)
		{
			indices[offset++] = (((i + 1) % sections) * sections) + ((j + 1) % sections);
			indices[offset++] = (((i + 1) % sections) * sections) + (j);
			indices[offset++] = (i * sections) + (j);

			indices[offset++] = (i * sections) + ((j + 1) % sections);
			indices[offset++] = (((i + 1) % sections) * sections) + ((j + 1) % sections);
			indices[offset++] = (i * sections) + (j);
		}
	}

	GLuint VBO, EBO;

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	IndiceCount = sizeof(indices) / sizeof(GLuint);
	DrawType = GL_TRIANGLES;
}

void CSphere::Render(CCamera * _gameCam)
{
	glUseProgram(m_program);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

	glBindVertexArray(m_VAO);
	glDrawElements(DrawType, IndiceCount, GL_UNSIGNED_INT, 0);
	
	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_BLEND);
}

