#ifndef MAT4_STRUCT_H
#define MAT4_STRUCT_H

#include <iostream>
#include "vec.h"
#include <glad/glad.h>

struct mat4
{
	GLfloat data[16];

	mat4();

	mat4(GLfloat s);

	mat4(float arr[16]);

	mat4(GLfloat m11, GLfloat m12, GLfloat m13, GLfloat m14,
		GLfloat m21, GLfloat m22, GLfloat m23, GLfloat m24,
		GLfloat m31, GLfloat m32, GLfloat m33, GLfloat m34,
		GLfloat m41, GLfloat m42, GLfloat m43, GLfloat m44);
};

mat4 mult(mat4 a, mat4 b);

void print(mat4 m);

mat4 generateProjection(float n, float f, float fov, float aspect);

mat4 generateTranslation(float xm, float ym, float zm);

mat4 generateTranslation(vec3 tr);

mat4 generateView(vec3 camPos, vec3 camDir, vec3 up, vec3 right);

mat4 generateScale(float sx, float sy, float sz);

mat4 generateScale(vec3 sc);

mat4 generateRotation(vec4 q);
#endif
