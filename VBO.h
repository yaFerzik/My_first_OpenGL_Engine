#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <iostream>
#include <glad/glad.h>
#include "vec.h"
#include <vector>

struct Vertex
{
	vec3 pos;
	vec3 norm;
	vec3 color;
	vec2 uv;
};

class VBO
{
public:
	GLuint id;

	VBO(std::vector<Vertex>& vertices);

	void Bind();

	void Unbind();

	void Destroy();
};

#endif