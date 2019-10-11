#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Utility.h"
#include "shapes.h"

class Terrain: public CShape
{
public:
	//struct InitInfo
	//{
	//	std::wstring HeightmapFilename;
	//	std::wstring LayerMapFilename0;
	//	std::wstring LayerMapFilename1;
	//	std::wstring LayerMapFilename2;
	//	std::wstring LayerMapFilename3;
	//	std::wstring LayerMapFilename4;
	//	std::wstring BlendMapFilename;
	//	float HeightScale;
	//	float HeightOffset;
	//	UINT NumRows;
	//	UINT NumCols;
	//	float CellSpacing;
	//};

	Terrain();
	~Terrain();

	//std::wstring HeightmapFilename = L"Resources/Heightmaps/H.raw";
	std::wstring HeightmapFilename = L"Resources/Heightmaps/coastMountain513.raw";
	float HeightScale = 0.35f;
	float HeightOffset = -20.0f;
	const UINT NumRows = 513;
	const UINT NumCols = 513;
	float CellSpacing = 1.0f;

	float width()const;
	float depth()const;
	float getHeight(float x, float y) const;

	void initialise(GLuint _program, GLuint _texture, float _x, float _y, float _z, float _scale);
	void Render(CCamera* _gameCam);

	// lighting stuff
	GLfloat specularStrength = 0.3f;
	GLfloat ambientStrength = 0.1f;

	glm::vec3 objectColor = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 lightPos = glm::vec3(0.0f, 10.0f, 0.0f);
	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

	//void init(ID3D10Device* device, const InitInfo& initInfo);

	//void setDirectionToSun(const D3DXVECTOR3& v);

	//void draw(const D3DXMATRIX& world);
private:
	void loadHeightmap();
	void smooth();
	bool inBounds(UINT i, UINT j);
	float average(UINT i, UINT j);
	void buildVB();
	void buildIB();

	//InitInfo mInfo;

	UINT mNumVertices;
	UINT mNumFaces;

	std::vector<GLuint> indices; // 3 indices per face

	std::vector<float> mHeightmap;

	

};

