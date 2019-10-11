#include "cubemap.h"

CCubeMap::CCubeMap()
{

}

//CCubeMap::CCubeMap(CCamera * _gameCam, std::vector<const char*> _filePaths)
//{
//	m_camera = _gameCam;
//	m_program = ShaderLoader::CreateProgram("Resources/Shaders/cubemap.verts", "Resources/Shaders/cubemap.frags");
//	//unsigned int textureID;
//	glGenTextures(1, &textureID);
//	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
//
//	int width, height;
//	unsigned char* image;
//	for (GLuint i = 0; i < 6; i++)
//	{
//		std::string fullPathName = "Resources/Textures/CubeMap/";
//		fullPathName.append(faces[i]);
//		image = SOIL_load_image(fullPathName.c_str(),
//			&width,
//			&height,
//			0,
//			SOIL_LOAD_RGBA);
//
//		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
//			0,
//			GL_RGBA,
//			width,
//			height,
//			0,
//			GL_RGBA,
//			GL_UNSIGNED_BYTE,
//			image);
//		SOIL_free_image_data(image);
//
//	}
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
//
//	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
//	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
//
//
//}

CCubeMap::CCubeMap(CCamera * _gameCam)
{
	m_camera = _gameCam;
	m_program = ShaderLoader::CreateProgram("Resources/Shaders/cubemap.verts", "Resources/Shaders/cubemap.frags");

	// VAO
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	// EBO
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// VBO
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Sending vertex data
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		3 * sizeof(GLfloat),	// Stride of the single vertex (pos)
		(GLvoid*)0);			// Offset from beginning of Vertex
	glEnableVertexAttribArray(0);

	//unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height;
	unsigned char* image;
	for (GLuint i = 0; i < 6; i++)
	{
		std::string fullPathName = "Resources/Textures/CubeMap/";
		fullPathName.append(faces[i]);
		image = SOIL_load_image(fullPathName.c_str(),
			&width,
			&height,
			0,
			SOIL_LOAD_RGBA);

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
			0,
			GL_RGBA,
			width,
			height,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			image);
		SOIL_free_image_data(image);

	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

}

CCubeMap::~CCubeMap()
{
	m_camera = nullptr;
}

void CCubeMap::Update()
{
	glm::mat4 model = glm::scale(glm::mat4(), glm::vec3(2000.0f, 2000.0f, 2000.0f));
	MVP = m_camera->getProjMat() * m_camera->getViewMat() * model;
}

void CCubeMap::Render()
{
	glUseProgram(m_program);
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	glUniform1i(glGetUniformLocation(m_program, "cubeSampler"), 0);
	glUniformMatrix4fv(glGetUniformLocation(m_program, "mvp"), 1, GL_FALSE, glm::value_ptr(MVP));

	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}
