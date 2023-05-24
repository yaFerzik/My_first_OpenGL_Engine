#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera(vec3 pos, float near, float far, float fov, float aspectRatio)
{
	this->pos = pos;
	this->near = near;
	this->far = far;
	this->fov = fov;
	this->aspectRatio = aspectRatio;

	yaw = 0.0;
	pitch = 0.0;

	updateDir();

	mouseClicked = false;
}

mat4 Camera::getMatrix(bool forSkybox)
{
	
	mat4 view = generateView(pos, dir, up, right);
	mat4 proj = generateProjection(near, far, fov, aspectRatio);

	if (forSkybox)
	{
		view.data[3] = 0;
		view.data[7] = 0;
		view.data[11] = 0;
		view.data[15] = 0;

		view.data[12] = 0;
		view.data[13] = 0;
		view.data[14] = 0;
	}
	return mult(proj, view);
}

void Camera::getInputs(GLFWwindow* window)
{
	int width, height;
	float pi = 3.141592653;
	float speed = 1.0 / 60.0;

	glfwGetWindowSize(window, &width, &height);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		pos = add(pos, mult(dir, speed));
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		pos = add(pos, mult(dir, -speed));
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		pos = add(pos, mult(right, speed));
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		pos = add(pos, mult(right, -speed));
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		pos = add(pos, mult(up, speed));
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		pos = add(pos, mult(up, -speed));
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		if (mouseClicked)
		{
			mouseClicked = false;
			glfwSetCursorPos(window, width / 2, height / 2);
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		mouseClicked = true;
	}

	if (mouseClicked)
	{
		double mouseX, mouseY;
		double sensetivity = 1.0;

		glfwGetCursorPos(window, &mouseX, &mouseY);

		double rotX = (mouseX - (double)width / 2.0) / (double)width * sensetivity;
		double rotY = (mouseY - (double)height / 2.0) / (double)width * sensetivity;

		yaw += rotX;
		pitch += rotY;

		if (pitch > pi / 2.0)
			pitch = pi / 2.0;
		if (pitch < -pi / 2.0)
			pitch = -pi / 2.0;

		updateDir();


		glfwSetCursorPos(window, width / 2, height / 2);
	}
}

void Camera::updateDir()
{
	dir = vec3{ cos(pitch) * sin(yaw), sin(pitch), cos(pitch) * cos(yaw) };
	right = normalize(vec3{ dir.z, 0.0, -dir.x });
	up = mult(normalize(cross(dir, right)), -1);
}