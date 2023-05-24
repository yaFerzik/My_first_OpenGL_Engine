#ifndef VEC_H
#define VEC_H
#include <iostream>
#include <glad/glad.h>

struct vec2
{
	GLfloat x, y;
};

struct vec3
{
	GLfloat x, y, z;

	vec3() {};

	vec3(GLfloat x, GLfloat y, GLfloat z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	vec3(GLfloat s)
	{
		this->x = s;
		this->y = s;
		this->z = s;
	}
};

struct vec4
{
	GLfloat x, y, z, w;

	vec4() {}

	vec4(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	vec4(GLfloat s)
	{
		this->x = s;
		this->y = s;
		this->z = s;
		this->w = s;
	}
};

float length(vec3 v);

float length(vec4 v);

vec3 normalize(vec3 v);

vec3 dot(vec3 a, vec3 b);

vec3 cross(vec3 a, vec3 b);

vec3 mult(vec3 v, float s);

vec3 add(vec3 a, vec3 b);

#endif