#pragma once

#include "glm\glm.hpp"
#include "glm\gtx\transform.hpp"
#include "GL\glew.h"

using namespace glm;
using namespace std;

class Camera
{
public:
	Camera(const vec3& pos, float fov, float aspect, float zNear, float zFar)
	{
		m_perspective = perspective(fov, aspect, zNear, zFar);
		m_pos = pos;
		m_foward = vec3(0, 0, 1);
		m_up = vec3(0, 1, 0);
	}

	inline mat4 GetViewProjection() const
	{
		return m_perspective * lookAt(m_pos, m_pos + m_foward, m_up);
	}

	inline vec3& GetPos() { return m_pos; }

private:
	mat4 m_perspective;
	vec3 m_pos;
	vec3 m_foward;
	vec3 m_up;

};

