#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include<json/json.h>
#include"Mesh.h"


using json = nlohmann::json;


class Model
{
public:
	Model(const char* file);

	void Draw(Shader& shader, Camera& camera, vec3 translation = vec3(0.0, 0.0, 0.0), 
		vec4 rotation = vec4(0.0, 0.0, 0.0, 1.0), vec3 scale = vec3(1.0, 1.0, 1.0));

private:
	// template variables
	const char* file;
	std::vector<unsigned char> data;
	json JSON;

	// transformations
	std::vector<Mesh> meshes;
	std::vector<vec3> translationsMeshes;
	std::vector<vec4> rotationsMeshes;
	std::vector<vec3> scalesMeshes;
	std::vector<mat4> matricesMeshes;

	// Loaded textures info
	std::vector<std::string> loadedTexName;
	std::vector<Texture> loadedTex;

	// Loads a single mesh by its index
	void loadMesh(unsigned int indMesh);

	// Traverses a node recursively, so it essentially traverses all connected nodes
	void traverseNode(unsigned int nextNode, mat4 matrix = mat4());

	// Gets the binary data from a file
	std::vector<unsigned char> getData();
	// Interprets the binary data into floats, indices, and textures
	std::vector<float> getFloats(json accessor);
	std::vector<GLuint> getIndices(json accessor);
	std::vector<Texture> getTextures();

	// Assembles all the floats into vertices
	std::vector<Vertex> assembleVertices
	(
		std::vector<vec3> positions,
		std::vector<vec3> normals,
		std::vector<vec2> texUVs
	);

	// Helps with the assembly from above by grouping floats
	std::vector<vec2> groupFloatsVec2(std::vector<float> floatVec);
	std::vector<vec3> groupFloatsVec3(std::vector<float> floatVec);
	std::vector<vec4> groupFloatsVec4(std::vector<float> floatVec);
};


#endif