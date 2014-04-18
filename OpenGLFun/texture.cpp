#include "texture.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>

using namespace std;

Texture::Texture(const string& path)
{
	int width, height, num_components;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &num_components, 4);

	if (data == NULL) cerr << "Texture Load Fail!! " << path << endl;

	glGenTextures(1, &im_texture);
	glBindTexture(GL_TEXTURE_2D, im_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);

}

void Texture::Bind(unsigned int unit)
{

	assert(unit >= 0 && unit <= 31);
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, im_texture);
}

Texture::~Texture()
{
	glDeleteTextures(1, &im_texture);
}
