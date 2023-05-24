#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad/glad.h>
#include "Shader.h"

class Texture
{
public:
	GLuint id;
	GLuint unit;
	const char* type;

	Texture() { type = NULL; }

	Texture(const char* filename, const char* texType, GLenum slot);

	void sendUniform(Shader& shader, const char* uniform, GLuint unit);

	void Bind();

	void Unbind();

	void Delete();
};

#endif