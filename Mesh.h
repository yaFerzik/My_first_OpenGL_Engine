#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "Shader.h"
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"
#include "Texture.h"
#include "Camera.h"

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	VAO vao;

	Mesh(std::vector<Vertex>& vertecies, std::vector<GLuint>& indices, std::vector<Texture>& textures);

	~Mesh();

	void Draw(Shader& shader, Camera& camera,
				mat4 matrix = mat4(),
				vec3 translation = vec3(0.0f),
				vec4 rotation = vec4(0.0f, 0.0f, 0.0f, 1.0f),
				vec3 scale = vec3(1.0f));
};

#endif