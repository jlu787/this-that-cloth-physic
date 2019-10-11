#include "tessmodel.h"

TessModel::TessModel(GLuint _program)
{
	GLfloat points[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		-1.0, 1.0, 0.0f
	};
	glPatchParameteri(GL_PATCH_VERTICES, 4); //comment for tri patch
	glGenBuffers(1, &m_VBO);
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glBindVertexArray(0);
}

TessModel::~TessModel()
{

}

void TessModel::Render(CCamera * _camera)
{
	glUseProgram(m_program);
	glm::vec3 objPosition = glm::vec3(m_posX, m_posY, m_posZ); // This is how much you will translate by
	glm::mat4 translationMatrix = glm::translate(glm::mat4(), objPosition); // create the transformation matrix

																			// Rotation
	glm::vec3 rotationAxis = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::mat4 rotationX = glm::rotate(glm::mat4(), glm::radians(m_rotX), rotationAxis);

	rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 rotationY = glm::rotate(glm::mat4(), glm::radians(m_rotY), rotationAxis);

	rotationAxis = glm::vec3(0.0f, 0.0f, 1.0f);
	glm::mat4 rotationZ = glm::rotate(glm::mat4(), glm::radians(m_rotZ), rotationAxis);

	// Scaling
	glm::vec3 objScale = glm::vec3(m_scaleX, m_scaleY, m_scaleZ);
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(), objScale);

	// Getting model matrix
	glm::mat4 model = translationMatrix * rotationX * rotationY * rotationZ * scaleMatrix;

	glm::mat4 mvp = _camera->getProjMat() * _camera->getViewMat() * model;

	GLint vpLoc = glGetUniformLocation(m_program, "mvp");
	glUniformMatrix4fv(vpLoc, 1, GL_FALSE, glm::value_ptr(mvp));

	glBindVertexArray(m_VAO);
	glDrawArrays(GL_PATCHES, 0, 4);
	glBindVertexArray(0);
}
