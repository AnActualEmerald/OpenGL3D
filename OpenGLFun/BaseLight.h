#pragma once
#include "glm\glm.hpp"
#include "shader.h"

using namespace std;
using namespace glm;

class BaseLight
{
public:
	BaseLight(vec3 col, float intensity) :
		color(col),
		intensity(intensity)
	{}
		//shader = Shader("./res/basicPhong");
		//	shader.Bind();
	//}

	~BaseLight(){}

	vec3& GetColor()
	{
		return color;
	}

	float& GetIntensity()
	{
		return intensity;
	}


private:
	int shader;
	vec3 color;
	float intensity;
};