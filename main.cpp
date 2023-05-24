#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "Model.h"
#include "ModelUtils.h"
#include "Skybox.h"
#include "FrameBuffer.h"

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* win = glfwCreateWindow(800, 600, "3D Renderer", NULL, NULL);
	if (win == NULL)
	{
		std::cout << "Error while creating a window\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(win);

	gladLoadGL();

	glViewport(0, 0, 800, 600);

	//-----------------------------------------------------------------------------

	Shader sh1 = Shader("default.vert", "default.frag");
	Shader skyboxShader = Shader("skybox.vert", "skybox.frag");
	Shader atmosphereShader = Shader("default.vert", "atmosphere.frag");
	Shader frameBufferShader = Shader("frameBuffer.vert", "frameBuffer.frag");

	Camera cam = Camera(vec3{ 0.0, 0.0, 0.0 }, 0.01, 1000.0, 3.1415 / 2.0, 800.0f / 600.0f);

	Skybox skybox1 = Skybox("C:\\Users\\User\\Desktop\\spaceSkyBox2\\", 0);

	vec3 lightDir = normalize(vec3(1.0, 0.3, 0.0));

	//Model m1 = Model("C:\\Users\\User\\Desktop\\airplane\\scene.gltf");

	float earthR = 1.0;
	float moonR = 0.33;
	float atmR = 1.5;

	Texture earthTexture = Texture("C:\\Users\\User\\Desktop\\2k_earth_daymap.jpg", "diffuse", 10); 
	Mesh earthMesh = createUVSphereMesh(earthR, 50, 50, earthTexture);

	Texture moonTexture = Texture("C:\\Users\\User\\Desktop\\2k_moon.jpg", "diffuse", 9);
	Mesh moonMesh = createUVSphereMesh(moonR, 50, 50, moonTexture);

	Texture atmosphereTexture = Texture();
	Mesh atmosphereMesh = createUVSphereMesh(atmR, 500, 500, atmosphereTexture);

	//-----------------------------------------------------------------------------


	float t = 0;

	
	// Enables Cull Facing
	glEnable(GL_CULL_FACE);
	// Keeps front faces
	glCullFace(GL_FRONT);
	// Uses counter clock-wise standard
	glFrontFace(GL_CW);
	// Main while loop

	FrameBuffer mainFrameBuffer(3);

	while (!glfwWindowShouldClose(win))
	{
		t += 3.1415 / 60;

		cam.getInputs(win);

		sh1.Activate();

		GLuint scUni = glGetUniformLocation(sh1.id, "lightDir");
		glUniform3f(scUni, lightDir.x, lightDir.y, lightDir.z);

		skyboxShader.Activate();
		glUniform3f(glGetUniformLocation(skyboxShader.id, "lightDir"), lightDir.x, lightDir.y, lightDir.z);

		//---------------------------------------------------

		vec3 r = normalize(vec3(0.0f, 1.0f, 0.0f));

		GLfloat earthRot = t / 20;
		vec4 earthQuat = vec4(sin(earthRot) * r.x, sin(earthRot) * r.y, sin(earthRot) * r.z, cos(earthRot));

		GLfloat moonRot = -t / 40;
		vec4 moonQuat = vec4(sin(moonRot) * r.x, sin(moonRot) * r.y, sin(moonRot) * r.z, cos(moonRot));

		float moonT = t / 20;
		float moonOrbitR = 6.0;
		vec3 moonPos = vec3(cos(moonT) * moonOrbitR, 0.0, sin(moonT) * moonOrbitR);
		//---------------------------------------------------
		
		mainFrameBuffer.Activate();

		glEnable(GL_DEPTH_TEST);

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		earthMesh.Draw(sh1, cam, mat4(), vec3(0.0f), earthQuat);
		moonMesh.Draw(sh1, cam, mat4(), moonPos, moonQuat);

		

		skybox1.Draw(skyboxShader, cam);
		
		mainFrameBuffer.Deactivate();

		atmosphereShader.Activate();
		glActiveTexture(GL_TEXTURE0 + mainFrameBuffer.slot);
		glBindTexture(GL_TEXTURE_2D, mainFrameBuffer.framebufferTexture);

		glUniform1i(glGetUniformLocation(atmosphereShader.id, "mainTex"), 3);
		vec3 camPos = cam.getPos();
		glUniform3f(glGetUniformLocation(atmosphereShader.id, "u_cameraPos"), camPos.x, camPos.y, camPos.z);
		glUniform3f(glGetUniformLocation(atmosphereShader.id, "u_planetPos"), 0.0, 0.0, 0.0);
		glUniform1f(glGetUniformLocation(atmosphereShader.id, "u_planetR"), earthR);
		glUniform1f(glGetUniformLocation(atmosphereShader.id, "u_atmR"), atmR);
		glUniform3f(glGetUniformLocation(atmosphereShader.id, "u_lightDir"), lightDir.x, lightDir.y, lightDir.z);

		vec3 scatteringCoefficients = vec3(
			pow(400.0 / 700.0, 4) * 3.0,
			pow(400.0 / 530.0, 4) * 3.0,
			pow(400.0 / 440.0, 4) * 3.0
		);

		glUniform1f(glGetUniformLocation(atmosphereShader.id, "u_density_falloff"), 16.f);
		glUniform1f(glGetUniformLocation(atmosphereShader.id, "u_scatteringPointsNum"), 10.f);
		glUniform1f(glGetUniformLocation(atmosphereShader.id, "u_opticalDepthPointsNum"), 10.f);
		glUniform3f(glGetUniformLocation(atmosphereShader.id, "u_sactteringCoefficients"), scatteringCoefficients.x, scatteringCoefficients.y, scatteringCoefficients.z);

		mainFrameBuffer.Activate();
		

		atmosphereMesh.Draw(atmosphereShader, cam);
		
		mainFrameBuffer.Deactivate();
		



		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		mainFrameBuffer.Draw(frameBufferShader);
		//---------------------------------------------------

		glfwSwapBuffers(win);
		glfwPollEvents();
	}
	
	sh1.Destroy();

	glfwDestroyWindow(win);
	glfwTerminate();
	return 0;
}