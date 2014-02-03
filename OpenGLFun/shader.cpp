#include "shader.h"
#include <iostream>
#include <fstream>

using namespace std;

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const string& errorMessage);
static string LoadShader(const string& fileName);
static GLuint CreateShader(const string& text, GLenum type);

Shader::Shader(const string& fileName)
{
	_program = glCreateProgram();
	_shaders[0] = CreateShader(LoadShader(fileName + ".vert"), GL_VERTEX_SHADER);
	_shaders[1] = CreateShader(LoadShader(fileName + ".frag"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
		glAttachShader(_program, _shaders[i]);
	
	glBindAttribLocation(_program, 0, "position");

	glLinkProgram(_program);
	CheckShaderError(_program, GL_LINK_STATUS, true, "Error Linking Shaders In " + fileName + ": Linking Failed");

	glValidateProgram(_program);
	CheckShaderError(_program, GL_VALIDATE_STATUS, true, "Error Linking Shaders In " + fileName + ": Validation Failed");

}

Shader::~Shader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(_program, _shaders[i]);
		glDeleteShader(_shaders[i]);
	}

	glDeleteProgram(_program);
}

void Shader::Bind()
{
	glUseProgram(_program);
}

GLuint CreateShader(const string& text, GLenum type)
{
	GLuint shader = glCreateShader(type);

	if (shader == 0)
		cerr << "Shader Creation Failed" << endl;

	const GLchar* src[1];
	GLint srcLengths[1];
	
	src[0] = text.c_str();
	srcLengths[0] = text.length();

	glShaderSource(shader, 1, src, srcLengths);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Shader Compiled Incorrectly");

	return shader;
}

string LoadShader(const std::string& fileName)
{
	ifstream file;
	file.open((fileName).c_str());

	string output;
	string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		std::cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		cerr << errorMessage << ": '" << error << "'" << endl;
	}
}


