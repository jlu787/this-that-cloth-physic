#include "terrain.h"

namespace
{
	struct TerrainVertex
	{
		glm::vec3 pos;
		glm::vec3 normal;
		glm::vec2 texC;
	};
}

Terrain::Terrain()
{
}

Terrain::~Terrain()
{
}

float Terrain::width() const
{
	return (NumCols-1)*CellSpacing;
}

float Terrain::depth() const
{
	return (NumRows - 1)*CellSpacing;
}

float Terrain::getHeight(float x, float z) const
{
	// Transform from terrain local space to "cell" space.
	float c = (x + 0.5f*width()) /  CellSpacing;
	float d = (z - 0.5f*depth()) / -CellSpacing;

	// Get the row and column we are in
	int row = (int)floorf(d);
	int col = (int)floorf(c);

	// Grab the heights of the cell we are in.
	// A*--*B
	//  | /|
	//  |/ |
	// C*--*D
	float A = mHeightmap[row* NumCols + col];
	float B = mHeightmap[row* NumCols + col + 1];
	float C = mHeightmap[(row + 1)* NumCols + col];
	float D = mHeightmap[(row + 1)* NumCols + col + 1];

	// Where we are relative to the cell.
	float s = c - (float)col;
	float t = d - (float)row;

	// If upper triangle ABC.
	if (s + t <= 1.0f)
	{
		float uy = B - A;
		float vy = C - A;
		return A + s * uy + t * vy;
	}
	else // lower triangle DCB.
	{
		float uy = C - D;
		float vy = B - D;
		return D + (1.0f - s)*uy + (1.0f - t)*vy;
	}
}

void Terrain::initialise(GLuint _program, GLuint _texture, float _x, float _y, float _z, float _scale)
{
	// load in the program
	m_program = _program;
	m_tex = _texture;

	m_posX = (float)_x;
	m_posY = (float)_y;
	m_posZ = (float)_z;

	m_scaleX = _scale;
	m_scaleY = _scale;
	m_scaleZ = _scale;

	loadHeightmap();
	smooth();

	buildVB();
}

void Terrain::Render(CCamera * _gameCam)
{
	glUseProgram(m_program);

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Translation

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

	// SENDING INFO TO THE VERTEX SHADER

	// Send model matrix
	GLuint modelLoc = glGetUniformLocation(m_program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	// MVP Matrix
	// Calculate the MVP matrix
	glm::mat4 MVP = _gameCam->getProjMat() * _gameCam->getViewMat() * model;
	// Send via uniform
	GLuint projLoc = glGetUniformLocation(m_program, "mvp");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(MVP));

	//// MVP Matrix
	//// Calculate the MVP matrix
	//glm::mat4 VP = _gameCam->getProjMat() * _gameCam->getViewMat();
	//// Send via uniform
	//GLuint projLoc = glGetUniformLocation(m_program, "vp");
	//glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(VP));

	// SENDING INFO TO THE FRAGMENT SHADER

	//// lighting
	//GLuint specLoc = glGetUniformLocation(m_program, "specularStrength");
	//glUniform1f(specLoc, specularStrength);

	//GLuint ambLoc = glGetUniformLocation(m_program, "ambientStrength");
	//glUniform1f(ambLoc, ambientStrength);

	//GLuint objColorLoc = glGetUniformLocation(m_program, "objectColor");
	//glUniform3fv(objColorLoc, 1, glm::value_ptr(objectColor));

	//GLuint lightPosLoc = glGetUniformLocation(m_program, "lightPos");
	//glUniform3fv(lightPosLoc, 1, glm::value_ptr(lightPos));

	//GLuint lightColorLoc = glGetUniformLocation(m_program, "lightColor");
	//glUniform3fv(lightColorLoc, 1, glm::value_ptr(lightColor));


	// Send cam pos
	GLuint camLoc = glGetUniformLocation(m_program, "camPos");
	glUniform3fv(camLoc, 1, glm::value_ptr(_gameCam->getCamPos()));

	// Bind Texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_tex);
	glUniform1i(glGetUniformLocation(m_program, "tex"), 0);

	glBindVertexArray(m_VAO);	// Bind VAO
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0); // Unbind VAO

	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	//glDisable(GL_BLEND);
}

void Terrain::loadHeightmap()
{
	// A height for each vertex
	std::vector<unsigned char> in( NumRows *  NumCols);

	// Open the file.
	std::ifstream inFile;
	inFile.open( HeightmapFilename.c_str(), std::ios_base::binary);

	if (inFile)
	{
		// Read the RAW bytes.
		inFile.read((char*)&in[0], (std::streamsize)in.size());

		// Done with file.
		inFile.close();
	}

	// Copy the array data into a float array, and scale and offset the heights.
	mHeightmap.resize( NumRows *  NumCols, 0);
	for (UINT i = 0; i <  NumRows *  NumCols; ++i)
	{
		mHeightmap[i] = (float)in[i] *  HeightScale +  HeightOffset;
	}
}

void Terrain::smooth()
{
	std::vector<float> dest(mHeightmap.size());

	for (UINT i = 0; i <  NumRows; ++i)
	{
		for (UINT j = 0; j <  NumCols; ++j)
		{
			dest[i* NumCols + j] = average(i, j);
		}
	}

	// Replace the old heightmap with the filtered one.
	mHeightmap = dest;
}

bool Terrain::inBounds(UINT i, UINT j)
{
	// True if ij are valid indices; false otherwise.
	return
		i >= 0 && i <  NumRows &&
		j >= 0 && j <  NumCols;
}

float Terrain::average(UINT i, UINT j)
{
	// Function computes the average height of the ij element.
	// It averages itself with its eight neighbor pixels.  Note
	// that if a pixel is missing neighbor, we just don't include it
	// in the average--that is, edge pixels don't have a neighbor pixel.
	//
	// ----------
	// | 1| 2| 3|
	// ----------
	// |4 |ij| 6|
	// ----------
	// | 7| 8| 9|
	// ----------

	float avg = 0.0f;
	float num = 0.0f;

	for (int m = i - 1; m <= i + 1; ++m)
	{
		for (int n = j - 1; n <= j + 1; ++n)
		{
			if (inBounds(m, n))
			{
				avg += mHeightmap[m* NumCols + n];
				num += 1.0f;
			}
		}
	}

	return avg / num;
}

void Terrain::buildVB()
{
	std::vector<TerrainVertex> vertices(NumCols * NumRows * 8);
	/*const int size = NumCols * NumRows * 8;
	GLfloat vertices[size];*/

	float halfWidth = ( NumCols - 1)* CellSpacing*0.5f;
	float halfDepth = ( NumRows - 1)* CellSpacing*0.5f;

	float du = 1.0f / ( NumCols - 1);
	float dv = 1.0f / ( NumRows - 1);
	for (UINT i = 0; i <  NumRows; ++i)
	{
		float z = halfDepth - i *  CellSpacing;
		for (UINT j = 0; j <  NumCols; ++j)
		{
			float x = -halfWidth + j *  CellSpacing;

			float y =  mHeightmap[i* NumCols + j];
			vertices[i* NumCols + j].pos = glm::vec3(x, y, z);
			vertices[i* NumCols + j].normal = glm::vec3(0.0f, 1.0f, 0.0f);

			// Stretch texture over grid.
			vertices[i* NumCols + j].texC.x = j * du;
			vertices[i* NumCols + j].texC.y = i * dv;
		}
	}

	// Estimate normals for interior nodes using central difference.
	float invTwoDX = 1.0f / (2.0f* CellSpacing);
	float invTwoDZ = 1.0f / (2.0f* CellSpacing);
	for (UINT i = 2; i <  NumRows - 1; ++i)
	{
		for (UINT j = 2; j <  NumCols - 1; ++j)
		{
			float t = mHeightmap[(i - 1)* NumCols + j];
			float b = mHeightmap[(i + 1)* NumCols + j];
			float l = mHeightmap[i* NumCols + j - 1];
			float r = mHeightmap[i* NumCols + j + 1];

			glm::vec3 tanZ(0.0f, (t - b)*invTwoDZ, 1.0f);
			glm::vec3 tanX(1.0f, (r - l)*invTwoDX, 0.0f);

			glm::vec3 N = glm::cross(tanZ, tanX);
			N = glm::normalize(N);

			vertices[i* NumCols + j].normal = N;
		}
	}


	// VAO
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	buildIB(); // get the indices

	//// EBO
	//glGenBuffers(1, &m_EBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// VBO
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(TerrainVertex), &vertices[0], GL_STATIC_DRAW);

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

										// Sending vertex data
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),	// Stride of the single vertex (pos)
		(GLvoid*)0);			// Offset from beginning of Vertex
	glEnableVertexAttribArray(0);

	//// Sending color data
	//glVertexAttribPointer(
	//	1,
	//	3,
	//	GL_FLOAT,
	//	GL_FALSE,
	//	8 * sizeof(GLfloat),	// Stride of the single vertex (pos)
	//	(GLvoid*)(3 * sizeof(GLfloat)));			// Offset from beginning of Vertex
	//glEnableVertexAttribArray(1);

		// Sending normal data
	glVertexAttribPointer(
		1,
		3,									// 3 floats for normals
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),				// Stride of the single vertex (pos)
		(GLvoid*)(3 * sizeof(GLfloat)));	// Offset from beginning of Vertex
	glEnableVertexAttribArray(1);

	// Sending texture data
	glVertexAttribPointer(
		2,
		2,									// 2 floats for texture coordinates
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(GLfloat),				// Stride of the single vertex (pos)
		(GLvoid*)(6 * sizeof(GLfloat)));	// Offset from beginning of Vertex
	glEnableVertexAttribArray(2);


}

void Terrain::buildIB()
{
	mNumFaces = (NumRows - 1) * (NumCols - 1) * 2;
	indices = std::vector<GLuint>(mNumFaces * 3); // 3 indices per face

	// Iterate over each quad and compute indices.
	int k = 0;
	for (GLuint i = 0; i <  NumRows - 1; ++i)
	{
		for (GLuint j = 0; j <  NumCols - 1; ++j)
		{
			indices[k] = i *  NumCols + j;
			indices[k + 1] = i *  NumCols + j + 1;
			indices[k + 2] = (i + 1)* NumCols + j;

			indices[k + 3] = (i + 1)* NumCols + j;
			indices[k + 4] = i *  NumCols + j + 1;
			indices[k + 5] = (i + 1)* NumCols + j + 1;

			k += 6; // next quad
		}
	}

	// EBO
	glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	/*D3D10_BUFFER_DESC ibd;
	ibd.Usage = D3D10_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(DWORD) * mNumFaces * 3;
	ibd.BindFlags = D3D10_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	D3D10_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = &indices[0];
	HR(md3dDevice->CreateBuffer(&ibd, &iinitData, &mIB));*/
}
