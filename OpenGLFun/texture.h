#pragma once

#include <string>
#include "GL/glew.h"

class Texture
{
public:
	Texture(const std::string& path);
	void Bind(unsigned int uint);
	~Texture();

private:

	GLuint im_texture;
	
};

