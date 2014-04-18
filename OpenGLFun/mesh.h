#pragma once

#include "glm\glm.hpp"
#include "GL\glew.h"
#include "obj_loader.h"
#include <string>

using namespace std;
using namespace glm;

class Vertex
{
public:
	Vertex(const vec3& pos, const vec2& texpos, const vec3& normal = vec3(0, 0, 0))
	{
		this->position = pos;
		this->texpos = texpos;
		this->normal = normal;
	}

	inline vec3* GetPos() { return &position;  }
	inline vec2* GetTexCoord() { return &texpos; }
	inline vec3* GetNormal() { return &normal; }


private:
	vec3 position;
	vec3 normal;
	vec2 texpos;
};


class Mesh
{
public:
	Mesh(Vertex* verts, unsigned int numVerts, unsigned int* indecies, unsigned int numIndecies);
	Mesh(const string& path);
	virtual ~Mesh();
	void draw();

private:

	void InitMesh(const IndexedModel& model);

	enum
	{
		POSITION_VB,
		TEXCOORD_VB,
		NORMAL_VB,

		INDEX_VB,

		NUM_BUFFERS
	};

	GLuint _vertArrayObj;
	GLuint _vertArrayBuffers[NUM_BUFFERS];
	unsigned int _drawCount;
};