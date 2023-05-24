#ifndef EBO_CLASS_H
#define EB_CLASS_H

#include <glad/glad.h>
#include <vector>

class EBO
{
	GLuint id;

public:
	EBO(std::vector<GLuint>& indices);

	void Bind();

	void Unbind();

	void Destroy();
};

#endif
