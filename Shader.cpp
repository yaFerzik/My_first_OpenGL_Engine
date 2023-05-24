#include "Shader.h"
#include <fstream>
#include <string>

Shader::Shader(const char* vertexShaderFile, const char* fragmentShaderFile)
{
	std::string vertexSource = getSourceCode(vertexShaderFile);
	std::string fragmentSource = getSourceCode(fragmentShaderFile);

	char* c_vertexSource = (char *)vertexSource.c_str();
	char* c_fragmentSource = (char *)fragmentSource.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	id = glCreateProgram();

	glShaderSource(vertexShader, 1, &c_vertexSource, NULL);
	glCompileShader(vertexShader);
	checkCompilation(vertexShader, "VERTEX");

	glShaderSource(fragmentShader, 1, &c_fragmentSource, NULL);
	glCompileShader(fragmentShader);
	checkCompilation(fragmentShader, "FRAGMENT");

	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);

	glLinkProgram(id);
	checkCompilation(id, "PROGRAM");

	//std::cout << c_vertexSource << "\n\n" << c_fragmentSource << "\n\n";

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

std::string Shader::getSourceCode(const char* filename)
{
	std::ifstream fin(filename);
	std::string line;
	std::string sourceCode = "";
	
	if (!fin.is_open())
	{
		std::cout << "Can't open shader file: " << filename << '\n';
		exit(-1);
	}

	while (!fin.eof())
	{
		getline(fin, line);
		sourceCode += line + '\n';
	}

	return sourceCode;
}

void Shader::Activate()
{
	glUseProgram(id);
}

void Shader::Destroy()
{
	glDeleteProgram(id);
}

void Shader::checkCompilation(GLuint shader, const char* type)
{
	GLint hasCompiled;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}