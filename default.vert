#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aUV;

out vec3 pos;
out vec3 norm;
out vec3 Color;
out vec2 UV;

out vec3 originalPos;

uniform mat4 camMat;
uniform mat4 modelMat;
uniform mat4 transMat;
uniform mat4 rotMat;
uniform mat4 scaleMat;

void main()
{
	//vec3 crntPos = vec3(modelMat * transMat * rotMat * scaleMat * vec4(aPos, 1.0));
	vec3 crntPos = vec3(modelMat * transMat * -rotMat * scaleMat * vec4(aPos, 1.0));
	//crntPos = aPos;

	originalPos = crntPos;

	gl_Position = camMat * vec4(crntPos, 1.0);

	//gl_Position = vec4(aPos, 1.0);

	pos = gl_Position.xyz / gl_Position.w;

	Color = aColor;
	UV = mat2(1.0, 0.0, 0.0, -1.0) * aUV;

	norm = vec3(rotMat * vec4(aNormal, 1.0));
}

