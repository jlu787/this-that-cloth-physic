#pragma once
#include <glew.h>
#include <freeglut.h> 
#include <SOIL.h> // Image loader
#include <fmod.hpp> // Audio
#include <glm.hpp> // Matrix
#include <gtc/matrix_transform.hpp> // Matrix
#include <gtc/type_ptr.hpp> // Matrix

#define UINT unsigned int

#define DAMPING 0.01
#define TIME_STEPSIZE2 0.5*0.5 // how large time step each particle takes each frame
#define CONSTRAINT_ITERATIONS 3 // how many iterations of constraint satisfaction each frame (more is rigid, less is soft)

class Utils
{
public:
	static const int SCR_WIDTH = 800;
	static const int SCR_HEIGHT = 800;
	static const float LEVEL_WIDTH;
	static const float LEVEL_HEIGHT;
	static GLuint loadTexture(const char* _file);

private:
};