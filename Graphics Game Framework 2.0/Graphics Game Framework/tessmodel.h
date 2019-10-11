#pragma once
#include "shapes.h"
#include "Utility.h"

class TessModel : public CShape
{
public:
	TessModel() {};
	TessModel(GLuint _program);
	~TessModel();

	void Render(CCamera* _camera);
private:
};
