#include "geometrymodel.h"

GeometryModel::GeometryModel()
{

}

GeometryModel::GeometryModel(GLuint program)
{
	m_program = program;

	GLfloat points[] = {
	0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, //passing in 1 point
	};

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glBindVertexArray(0);
}

//GeometryModel::GeometryModel(GLuint program, CCamera* camera) {
//	m_program = program;
//	m_camera = camera;
//	GLfloat points[] = {
//	0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, //passing in 1 point
//	};
//
//	glBindVertexArray(m_VAO);
//	glGenBuffers(1, &m_VBO);
//	glGenVertexArrays(1, &m_VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//	glBindVertexArray(0);
//}

GeometryModel::~GeometryModel()
{
}

void GeometryModel::Render(CCamera * _camera)
{
	glUseProgram(m_program);
	/*glm::mat4 model;
	glm::vec3 position = glm::vec3(m_posX, m_posY, m_posZ);
	model = glm::translate(model, position);
	glm::mat4 mvp = _camera->getProjMat() * _camera->getViewMat() * model;*/

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
	glDrawArrays(GL_POINTS, 0, 1);
	glBindVertexArray(0);
}

//void GeometryModel::Render()
//{
//	glUseProgram(m_program);
//	glm::mat4 model;
//	glm::vec3 position = glm::vec3(m_posX, m_posY, m_posZ);
//	model = glm::translate(model, position);
//	glm::mat4 mvp = m_camera->getProjMat() * m_camera->getViewMat() * model;
//	GLint vpLoc = glGetUniformLocation(m_program, "mvp");
//	glUniformMatrix4fv(vpLoc, 1, GL_FALSE, glm::value_ptr(mvp));
//	glBindVertexArray(m_VAO);
//	glDrawArrays(GL_POINTS, 0, 1);
//	glBindVertexArray(0);
//}
