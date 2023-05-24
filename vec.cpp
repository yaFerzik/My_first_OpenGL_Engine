#include "vec.h"

float length(vec3 v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

float length(vec4 v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}


vec3 normalize(vec3 v)
{
	float l = length(v);

	return vec3{ v.x / l, v.y / l, v.z / l };
}

vec3 dot(vec3 a, vec3 b)
{
	return vec3{ a.x * b.x, a.y * b.y, a.z * b.z};
}

vec3 cross(vec3 a, vec3 b)
{
	return vec3{ a.y * b.z - a.z * b.y,
				 a.z * b.x - a.x * b.z,
				 a.x * b.y - a.y * b.x };
}

vec3 mult(vec3 v, float s)
{
	return vec3{ v.x * s, v.y * s, v.z * s };
}

vec3 add(vec3 a, vec3 b)
{
	return vec3{ a.x + b.x, a.y + b.y, a.z + b.z };
}