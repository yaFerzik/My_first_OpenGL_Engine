#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <iostream>
#include <glad/glad.h>

class Shader
{
	std::string getSourceCode(const char* filename);

	void checkCompilation(GLuint shader, const char* type);

public:
	GLuint id;

	Shader(const char* vertexShaderFile, const char* fragmentShaderFile);

	void Activate();

	void Destroy();
};

#endif