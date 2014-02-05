#pragma once

#include "glm\glm.hpp"
#include "GL\glew.h"

using namespace std;
using namespace glm;

class Vertex
{
public:
	Vertex(const vec3& pos)
	{
		this->position = pos;
	}
private:
	vec3 position;
};


class Mesh
{
public:
	Mesh(Vertex* verts, unsigned int numVerts);
	virtual ~Mesh();
	void draw();

private:

	enum
	{
		POSITION_VB,

		NUM_BUFFERS
	};

	GLuint _vertArrayObj;
	GLuint _vertArrayBuffers[NUM_BUFFERS];
	unsigned int _drawCount;
};