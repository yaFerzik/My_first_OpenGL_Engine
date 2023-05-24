#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include "mat4.h"
#include <GLFW/glfw3.h>

class Camera
{
	vec3 pos;
	
	float pitch;
	float yaw;

	vec3 dir;
	vec3 up;
	vec3 right;

	float near;
	float far;
	float fov;
	float aspectRatio;

	bool mouseClicked;

	void updateDir();

public:
	Camera(vec3 pos, float near, float far, float fov, float aspectRatio);

	mat4 getMatrix(bool forSkybox = false);

	void getInputs(GLFWwindow* window);

	vec3 getPos() { return pos; }
};

#endif

