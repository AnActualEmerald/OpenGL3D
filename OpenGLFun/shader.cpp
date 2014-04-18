#include "shader.h"
#include <iostream>
#include <fstream>

using namespace std;

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const string& errorMessage);
static string LoadShader(const string& fileName);
static GLuint CreateShader(const string& text, GLenum type);
vec3 Shader::ambientLight = vec3(1, 1, 1);

Shader::Shader(const string& fileName)
{
	_program = glCreateProgram();
	_shaders[0] = CreateShader(LoadShader(fileName + ".vert"), GL_VERTEX_SHADER);
	_shaders[1] = CreateShader(LoadShader(fileName + ".frag"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
		glAttachShader(_program, _shaders[i]);
	
	glBindAttribLocation(_program, 0, "position");
	glBindAttribLocation(_program, 1, "texCoord");
	glBindAttribLocation(_program, 2, "normal");

	glLinkProgram(_program);
	CheckShaderError(_program, GL_LINK_STATUS, true, "Error Linking Shaders In " + fileName + ": Linking Failed");

	glValidateProgram(_program);
	CheckShaderError(_program, GL_VALIDATE_STATUS, true, "Error Linking Shaders In " + fileName + ": Validation Failed");


	_uniforms[PROJTRANSFORM_U] = glGetUniformLocation(_program, "projected_trans");
	_uniforms[TRANSFORM_U] = glGetUniformLocation(_program, "transform");
	_uniforms[AMBIENT_U] = glGetUniformLocation(_program, "ambientLight");
	_uniforms[DIRLIGHT_COL_U] = glGetUniformLocation(_program, "dirLight.base.color");
	_uniforms[DIRLIGHT_DIR_U] = glGetUniformLocation(_program, "dirLight.dir");
	_uniforms[DIRLIGHT_INTENSE_U] = glGetUniformLocation(_program, "dirLight.base.intensity");
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

void Shader::Update(const Transform& trans, const Camera& cam)
{
	glm::mat4 model = cam.GetViewProjection() * trans.GetModel();
	glUniformMatrix4fv(_uniforms[PROJTRANSFORM_U], 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(_uniforms[TRANSFORM_U], 1, GL_FALSE, &trans.GetModel()[0][0]);
	glUniform3f(_uniforms[AMBIENT_U], ambientLight.x, ambientLight.y, ambientLight.z);
	glUniform3f(_uniforms[DIRLIGHT_COL_U], dirLight.GetBase().GetColor().x, dirLight.GetBase().GetColor().y, dirLight.GetBase().GetColor().z);
	glUniform3f(_uniforms[DIRLIGHT_DIR_U], dirLight.GetDir().x, dirLight.GetDir().y, dirLight.GetDir().z);
	glUniform1f(_uniforms[DIRLIGHT_INTENSE_U], dirLight.GetBase().GetIntensity());
}

void Shader::SetDirLight(const DirectionalLight& light)
{
	this->dirLight = light;
}

void Shader::SetAmbience(const vec3& amb)
{
	ambientLight = amb;
}

vec3& Shader::GetAmbience()
{
	return ambientLight;
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


