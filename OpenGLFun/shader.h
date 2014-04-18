#pragma once

#include <string>
#include <GL\glew.h>
#include "transform.h"
#include "camera.h"
#include "directionallight.h"

class Shader
{
public:
	Shader(const std::string& fileName);
	Shader();
	virtual ~Shader();
	
	void Bind();
	void Update(const Transform&, const Camera&);

	void SetDirLight(const DirectionalLight& light);

	void SetAmbience(const vec3&);
	vec3& GetAmbience();

protected:
	static const int NUM_SHADERS = 2;
	static vec3 ambientLight;
	DirectionalLight dirLight = DirectionalLight(BaseLight(vec3(1, 1, 1), 0.8), vec3(0, 1, 0));

private:

	enum
	{
		PROJTRANSFORM_U,
		AMBIENT_U,
		TRANSFORM_U,
		DIRLIGHT_COL_U,
		DIRLIGHT_DIR_U,
		DIRLIGHT_INTENSE_U,

		NUM_UNIFORMS
	};

	GLuint _program;
	GLuint _shaders[NUM_SHADERS];
	GLuint _uniforms[NUM_UNIFORMS];
};

