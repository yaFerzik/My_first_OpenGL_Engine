#include "ModelUtils.h"

Mesh createFlatPanelMesh(float width, float height, int nodesW, int nodesH, Texture& tex)
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	textures.push_back(tex);

	float x0 = -width / 2.f;
	float y0 = -height / 2.f;

	float dx = width / nodesW;
	float dy = height / nodesH;

	vec3 normal = vec3(0.0, 1.0, 0.0);

	for (int i = 0; i < nodesW; i++)
		for (int j = 0; j < nodesH; j++)
		{
			float x = x0 + dx * i;
			float y = y0 + dy * j;

			float u = (float)i / (float)(nodesW - 1);
			float v = (float)j / (float)(nodesH - 1);

			vec3 pos = vec3(x, 0, y);
			vec2 uv = vec2{ u, v };


			vertices.push_back(Vertex{ pos, normal, vec3(1.0), uv });
		}

	for (int i = 0; i < nodesW - 1; i++)
		for (int j = 0; j < nodesH - 1; j++)
		{
			int i00 = i * nodesH + j;
			int i10 = (i + 1) * nodesH + j;
			int i01 = i * nodesH + j + 1;
			int i11 = (i + 1) * nodesH + j + 1;

			indices.push_back(i00);
			indices.push_back(i01);
			indices.push_back(i11);
			indices.push_back(i00);
			indices.push_back(i11);
			indices.push_back(i10);
		}

	return Mesh(vertices, indices, textures);
}

Mesh createUVSphereMesh(float r, int numStacks, int numSlices, Texture& tex)
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	textures.push_back(tex);

	vertices.push_back(Vertex{ vec3(0.0, r, 0.0), vec3(0.0, 1.0, 0.0), vec3(1.0), vec2{0.0, 0.0} });

	for (int i = 0; i < numStacks; i++)
	{
		float phi = PI * (float)(i + 1) / (float)(numStacks + 1);
		for (int j = 0; j < numSlices; j++)
		{
			float theta = PI * 2.0 * (float)j / (float)(numSlices - 1);

			float x = r * sin(phi) * cos(theta);
			float y = r * cos(phi);
			float z = r * sin(phi) * sin(theta);

			vec3 pos = vec3(x, y, z);
			vec3 norm = normalize(pos);
			vec3 color = vec3(1.0, 1.0, 1.0);
			vec2 uv = vec2{ (float)(theta / 2.0 / PI), (float)(phi / PI) };

			vertices.push_back(Vertex{ pos, norm, color, uv });
		}
	}
	vertices.push_back(Vertex{ vec3(0.0, -r, 0.0), vec3(0.0, -1.0, 0.0), vec3(1.0), vec2{0.0, 1.0} });

	//---------------------------------------------------------------

	for (int i = 0; i < numSlices - 1; i++)
	{
		int i0 = 0;
		int i1 = i + 1;
		int i2 = i + 2;

		indices.push_back(i0);
		indices.push_back(i1);
		indices.push_back(i2);
	}

	for (int i = 0; i < (numStacks - 1) * numSlices; i++)
	{
		if (i % numSlices == (numSlices - 1))
			continue;

		int i00 = i + 1;
		int i10 = i + 2;
		int i01 = i + numSlices + 1;
		int i11 = i + numSlices + 2;

		indices.push_back(i00);
		indices.push_back(i01);
		indices.push_back(i11);
		indices.push_back(i00);
		indices.push_back(i11);
		indices.push_back(i10);
	}

	for (int i = 0; i < numSlices - 1; i++)
	{
		int i0 = numStacks * numSlices + 1;
		int i1 = numSlices * (numStacks - 1) + 1 + i;
		int i2 = i1 + 1;

		indices.push_back(i0);
		indices.push_back(i2);
		indices.push_back(i1);
	}

	//---------------------------------------------------------------

	return Mesh(vertices, indices, textures);
}