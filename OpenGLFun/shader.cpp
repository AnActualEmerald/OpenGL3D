#include "shader.h"
#include <iostream>
#include <fstream>

using namespace std;


Shader::Shader(const string& fileName)
{

}

Shader::~Shader()
{
}

string Shader::LoadShader(const std::string& fileName)
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

