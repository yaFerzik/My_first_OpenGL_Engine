#ifndef SKYBOX_H
#define SKYBOX_H

#include "Mesh.h"

class Skybox
{
	GLuint vao;
	unsigned int cubemapTexture;
	int unit;
public:
	Skybox(std::string directory, int slot);

	void Draw(Shader& shader, Camera& camera);

	int getLocation() { return unit; }
};

#endif // !SKYBOX_H
