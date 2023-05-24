#include "Mesh.h"
#include <string>

Mesh::Mesh(std::vector<Vertex>& verteces, std::vector<GLuint>& indices, std::vector<Texture>& textures)
{
	this->vertices = verteces;
	this->indices = indices;
	this->textures = textures;

	vao.Bind();

	VBO vbo1 = VBO(this->vertices);

	EBO ebo1 = EBO(this->indices);

	vao.LinkAttribute(vbo1, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	vao.LinkAttribute(vbo1, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(sizeof(GLfloat) * 3));
	vao.LinkAttribute(vbo1, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(sizeof(GLfloat) * 6));
	vao.LinkAttribute(vbo1, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(sizeof(GLfloat) * 9));

	vao.Unbind();
	vbo1.Unbind();
	ebo1.Unbind();

}

void Mesh::Draw(Shader& shader, Camera& camera, mat4 matrix, vec3 translation, vec4 rotation, vec3 scale)
{
	int diffNum = 0;
	int specNum = 0;

	shader.Activate();

	for (int i = 0; i < textures.size(); i++)
	{
		if (textures[i].type == NULL)
			continue;

		std::string type = textures[i].type;
		std::string num;

		if (type == "diffuse")
			num = std::to_string(diffNum++);
		else if (type == "specular")
			num = std::to_string(specNum++);

		textures[i].sendUniform(shader, (type + num).c_str(), i);
		textures[i].Bind();
	}

	GLuint matUni = glGetUniformLocation(shader.id, "camMat");
	mat4 viewProj = camera.getMatrix();
	glUniformMatrix4fv(matUni, 1, GL_FALSE, viewProj.data);

	mat4 trans = generateTranslation(translation.x, translation.y, translation.z);
	mat4 rot = generateRotation(rotation);
	mat4 sc = generateScale(scale.x, scale.y, scale.z);

	GLuint modUni = glGetUniformLocation(shader.id, "modelMat");
	glUniformMatrix4fv(modUni, 1, GL_FALSE, matrix.data);
	GLuint transUni = glGetUniformLocation(shader.id, "transMat");
	glUniformMatrix4fv(transUni, 1, GL_FALSE, trans.data);
	GLuint rotUni = glGetUniformLocation(shader.id, "rotMat");
	glUniformMatrix4fv(rotUni, 1, GL_FALSE, rot.data);
	GLuint scUni = glGetUniformLocation(shader.id, "scaleMat");
	glUniformMatrix4fv(scUni, 1, GL_FALSE, sc.data);

	vao.Bind();
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	vao.Unbind();
}

Mesh::~Mesh()
{
	
}