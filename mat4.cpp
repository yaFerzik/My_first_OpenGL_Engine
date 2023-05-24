#include "mat4.h"

mat4::mat4()
{
	GLfloat ndata[] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
	for (int i = 0; i < 16; i++)
		data[i] = ndata[i];
		
}

mat4::mat4(GLfloat s)
{
	for (int i = 0; i < 16; i++)
		data[i] = s;
}

mat4::mat4(GLfloat m11, GLfloat m21, GLfloat m31, GLfloat m41,
			GLfloat m12, GLfloat m22, GLfloat m32, GLfloat m42,
			GLfloat m13, GLfloat m23, GLfloat m33, GLfloat m43,
			GLfloat m14, GLfloat m24, GLfloat m34, GLfloat m44)
{
	data[0] = m11;
	data[1] = m21;
	data[2] = m31;
	data[3] = m41;

	data[4] = m12;
	data[5] = m22;
	data[6] = m32;
	data[7] = m42;

	data[8] = m13;
	data[9] = m23;
	data[10] = m33;
	data[11] = m43;

	data[12] = m14;
	data[13] = m24;
	data[14] = m34;
	data[15] = m44;

}

mat4::mat4(float arr[16])
{
	for (int i = 0; i < 16; i++)
	{
		int x = i % 4;
		int y = i / 4;

		//data[x * 4 + y] = arr[i];
		data[i] = arr[i];
	}
}


mat4 mult(mat4 a, mat4 b)
{
	mat4 c;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			float sum = 0;
			for (int k = 0; k < 4; k++)
				//sum += a.data[i + k * 4] * b.data[k + j * 4];
				sum += a.data[i + k * 4] * b.data[k + j * 4];
			c.data[i + j * 4] = sum;
		}
	return c;
}

void print(mat4 m)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			std::cout << m.data[i + j * 4] << " ";
		std::cout << '\n';
	}
	std::cout << "\n";
}

mat4 generateProjection(float n, float f, float fov, float aspect)
{
	float nDivTan = tan(fov / 2.0);
	/*
	mat4 m = mat4{ nDivTan, 0, 0, 0,	0, nDivTan, 0, 0,		0, 0, (f + n), -f * n,			0, 0, 1, 0 };
	mat4 m2 = mat4{ 1, 0, 0, 0,			0, 1, 0, 0,				0, 0, 2.0f / (f - n), 0,		0, 0, 0, 1 };
	mat4 m3 = mat4{ 1, 0, 0, 0,			0, 1, 0, 0,				0, 0, 1, -n - (f - n) / 2.0f,	0, 0, 0, 1 };
	*/

	mat4 m = mat4{ nDivTan, 0, 0, 0,	0, nDivTan * aspect, 0, 0,		0, 0, f + n, 1,				0, 0, -f * n, 0 };
	mat4 m2 = mat4{ 1, 0, 0, 0,			0, 1, 0, 0,						0, 0, 2.0f / (f - n), 0,	0, 0, 0, 1 };
	mat4 m3 = mat4{ 1, 0, 0, 0,			0, 1, 0, 0,						0, 0, 1, 0,					0, 0, -n - (f - n) / 2.0f, 1 };

	mat4 m4 = mult(m2, m3);
	mat4 m5 = mult(m4, m);

	return m5;
}

mat4 generateTranslation(float xm, float ym, float zm)
{
	//mat4 m = mat4{ 1, 0, 0, -xm,		0, 1, 0, -ym,		0, 0, 1, -zm,		0, 0, 0, 1 };
	mat4 m = mat4{ 1, 0, 0, 0,          0, 1, 0, 0,		0, 0, 1, 0,		xm, ym, zm, 1 };
	return m;
}

mat4 generateTranslation(vec3 tr)
{
	return generateTranslation(tr.x, tr.y, tr.z);
}

mat4 generateView(vec3 camPos, vec3 camDir, vec3 up, vec3 right)
{
	mat4 trans = generateTranslation(-camPos.x, -camPos.y, -camPos.z);

	mat4 view = mat4{ right.x, up.x, camDir.x, 0.0,
					  right.y, up.y, camDir.y, 0.0,
					  right.z, up.z, camDir.z, 0.0,
					  0.0,	   0.0,	 0.0,	   1.0 };

	return mult(view, trans);
}

mat4 generateScale(float sx, float sy, float sz)
{
	mat4 scale = mat4{ sx, 0, 0, 0,  0, sy, 0, 0, 0, 0, sz, 0, 0, 0, 0, 1 };
	return scale;
}

mat4 generateScale(vec3 sc)
{
	return generateTranslation(sc.x, sc.y, sc.z);
}

mat4 generateRotation(vec4 q)
{
	/*
	GLfloat s = length(q);
	s = 1.0 / (s * s);

	q.y = -q.y;

	mat4 r = mat4{ 1.0f - 2.0f * s * (q.y * q.y + q.z * q.z), 2.0f * s * (q.x * q.y + q.z * q.w), 2.0f * s * (q.x * q.z - q.y * q.w), 0.0f,
				   2.0f * s * (q.x * q.y - q.z * q.w), 1.0f - 2.0f * s * (q.x * q.x + q.z * q.z), 2.0f * s * (q.y * q.z + q.x * q.w), 0.0f,
				   2.0f * s * (q.x * q.z + q.y * q.w), 2.0f * s * (q.y * q.z - q.x * q.w), 1.0f - 2.0f * s * (q.x * q.x + q.y * q.y), 0.0f,
				   0.0f,							   0.0f,							   0.0f,									  1.0f};

	return r;
	*/

	GLfloat s = length(q);

	q.x = q.x / s;
	q.y = q.y / s;
	q.z = q.z / s;
	q.w = q.w / s;

	mat4 r = mat4{ 1 - 2 * q.y * q.y - 2 * q.z * q.z,		2 * q.x * q.y + 2 * q.w * q.z,		2 * q.x * q.z - 2 * q.w * q.y,		0,
				   2 * q.x * q.y - 2 * q.w * q.z,			1 - 2 * q.x * q.x - 2 * q.z * q.z,	2 * q.y * q.z + 2 * q.w * q.x,		0,
				   2 * q.x * q.z + 2 * q.w * q.y,			2 * q.y * q.z - 2 * q.w * q.x,		1 - 2 * q.x * q.x - 2 * q.y * q.y,	0,
				   0,										0,									0,									1 };
	return r;
}