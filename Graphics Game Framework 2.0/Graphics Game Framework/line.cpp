#include "line.h"

void CLine::initailise(GLuint _program, glm::vec3 _pos1, glm::vec3 _pos2)
{
	m_program = _program;
	m_pos1 = _pos1;
	m_pos2 = _pos2;

	// load in the program

	// VAO
	glGenVertexArrays(1, &m_VAO);
	/*glBindVertexArray(m_VAO);*/


	//// EBO
	//glGenBuffers(1, &m_EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//// VBO
	//glGenBuffers(1, &m_VBO);
	//glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	//// Sending vertex data
	//glVertexAttribPointer(
	//	0,
	//	3,
	//	GL_FLOAT,
	//	GL_FALSE,
	//	6 * sizeof(GLfloat),	// Stride of the single vertex (pos)
	//	(GLvoid*)0);			// Offset from beginning of Vertex
	//glEnableVertexAttribArray(0);

	//// Sending color data
	//glVertexAttribPointer(
	//	1,
	//	3,
	//	GL_FLOAT,
	//	GL_FALSE,
	//	6 * sizeof(GLfloat),	// Stride of the single vertex (pos)
	//	(GLvoid*)(3 * sizeof(GLfloat)));			// Offset from beginning of Vertex
	//glEnableVertexAttribArray(1);

	//// Sending texture data
	//glVertexAttribPointer(
	//	2,
	//	2,									// 2 floats for texture coordinates
	//	GL_FLOAT,
	//	GL_FALSE,
	//	8 * sizeof(GLfloat),
	//	(GLvoid*)(6 * sizeof(GLfloat)));
	//glEnableVertexAttribArray(2);
}

void CLine::Render(CCamera * _gameCam)
{
	glUseProgram(m_program);

	/*glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/

	 //Translation

	////glm::vec3 objPosition = glm::vec3(m_posX, m_posY, m_posZ); // This is how much you will translate by
	//glm::mat4 translationMatrix = glm::translate(glm::mat4(), m_pos1); // create the transformation matrix

	//																		// Rotation
	//float rotX = 0.0f, rotY = 0.0f, rotZ = 0.0f;

	//// X axis
	//glm::vec3 rotationAxis = glm::vec3(1.0f, 0.0f, 0.0f);
	//rotX = atan2(m_pos2.y - m_pos1.y, m_pos2.z - m_pos1.z);
	//glm::mat4 rotationX = glm::rotate(glm::mat4(), (rotX), rotationAxis);

	//// Y axis
	//rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	//rotY = atan2(m_pos2.z - m_pos1.z, m_pos2.x - m_pos1.x);
	//glm::mat4 rotationY = glm::rotate(glm::mat4(), (rotY), rotationAxis);

	//// Z axis
	//rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
	//rotZ = atan2(m_pos2.y - m_pos1.y, m_pos2.x - m_pos1.x);
	//glm::mat4 rotationZ = glm::rotate(glm::mat4(), (rotZ), rotationAxis);

	//// Scaling
	//float scaleDistance = glm::distance(m_pos1, m_pos2);
	//glm::vec3 objScale = glm::vec3(scaleDistance, scaleDistance, scaleDistance);
	//glm::mat4 scaleMatrix = glm::scale(glm::mat4(), objScale);

	//// Getting model matrix
	//glm::mat4 model = translationMatrix * /*rotationX * rotationY **/ rotationZ * scaleMatrix;

	//// MVP Matrix
	//// Calculate the MVP matrix
	//glm::mat4 MVP = _gameCam->getProjMat() * _gameCam->getViewMat() * model;
	//// Send via uniform
	//GLuint projLoc = glGetUniformLocation(m_program, "mvp");
	//glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(MVP));

	// Trying to send only world position data

	//glm::vec4 pos1Data = _gameCam->getProjMat() * _gameCam->getViewMat() * glm::vec4(m_pos1.x, m_pos1.y, m_pos1.z, 1.0f);
	//glm::vec4 pos2Data = _gameCam->getProjMat() * _gameCam->getViewMat() * glm::vec4(m_pos2.x, m_pos2.y, m_pos2.z, 1.0f);

	//// point 1
	//vertices[0] = pos1Data.x;
	//vertices[1] = pos1Data.y;
	//vertices[2] = pos1Data.z;

	//// point 2
	//vertices[6] = pos2Data.x;
	//vertices[7] = pos2Data.y;
	//vertices[8] = pos2Data.z;

	// Send pos 1
	GLuint pos1Loc = glGetUniformLocation(m_program, "pos1");
	glUniform3fv(pos1Loc, 1, glm::value_ptr(m_pos1));

	// Send pos 2
	GLuint pos2Loc = glGetUniformLocation(m_program, "pos2");
	glUniform3fv(pos2Loc, 1, glm::value_ptr(m_pos2));

	// send vp
	glm::mat4 VP = _gameCam->getProjMat() * _gameCam->getViewMat();
	GLuint projLoc = glGetUniformLocation(m_program, "vp");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(VP));

	// Send color
	GLuint colorLoc = glGetUniformLocation(m_program, "lineColor");
	glUniform3fv(colorLoc, 1, glm::value_ptr(m_color));

	glBindVertexArray(m_VAO);	// Bind VAO
	//glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
	glDrawArrays(GL_POINTS, 0, 1);
	glBindVertexArray(0); // Unbind VAO

	glUseProgram(0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);
	//glBindTexture(GL_TEXTURE_2D, 0);
	//glDisable(GL_BLEND);
}
