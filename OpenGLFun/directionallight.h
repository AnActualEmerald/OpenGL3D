#pragma once
#include "BaseLight.h"
#include "glm\glm.hpp"

using namespace glm;

class DirectionalLight
{
public:

	DirectionalLight(const BaseLight& base, const vec3& dir):
		base(base)
		{
			float len = dir.length();
			this->dir = dir;
			this->dir.x /= std::abs(len);
			this->dir.y /= std::abs(len);
			this->dir.z /= std::abs(len);

		}

	~DirectionalLight() {}

	vec3& GetDir()
	{
		return dir;
	}

	BaseLight& GetBase()
	{
		return base;
	}

private:
	BaseLight base;
	vec3 dir;
};

