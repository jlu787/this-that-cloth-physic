#pragma once

#include "shapes.h"

class GeometryModel: public CShape
{
public:
	GeometryModel();
	GeometryModel(GLuint program);
	~GeometryModel();

	void Render(CCamera* _camera);

private:
	//CCamera* m_camera;
};
