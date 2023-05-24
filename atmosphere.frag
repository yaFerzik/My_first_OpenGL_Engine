#version 330 core
out vec4 FragColor;


in vec3 pos;
in vec3 norm;
in vec3 Color;
in vec2 UV;

in vec3 originalPos;

uniform sampler2D mainTex;

uniform vec3 u_cameraPos;
uniform vec3 u_planetPos;
uniform float u_planetR;
uniform float u_atmR;

uniform vec3 u_lightDir;

uniform float u_density_falloff;
uniform float u_scatteringPointsNum;
uniform float u_opticalDepthPointsNum;

uniform vec3 u_sactteringCoefficients;

vec2 sphIntersect( in vec3 ro, in vec3 rd, in vec3 ce, float ra )
{
    vec3 oc = ro - ce;
    float b = dot( oc, rd );
    float c = dot( oc, oc ) - ra*ra;
    float h = b*b - c;
    if( h<0.0 ) return vec2(-1.0); // no intersection
    h = sqrt( h );
    return vec2( -b-h, -b+h );
}

float raySphere(in vec3 ro, in vec3 rd, in vec3 ce, float ra)
{
	vec2 inter = sphIntersect(ro, rd, ce, ra);

	if (inter.x == -1.0 && inter.y == -1.0)
		return -1.0;
	return inter.y - max(0.0, inter.x);
}

float densityAtPoint(vec3 samplePoint)
{
	float denstyFalloff = u_density_falloff;

	float surfHeight = length(samplePoint - u_planetPos) - u_planetR;
	float height1 = surfHeight / (u_atmR - u_planetR);

	return exp(-height1 * denstyFalloff) * (1.0 - height1);
}

float opticalDepth(vec3 rayOrigin, vec3 rayDir, float rayLength)
{
	vec3 densitySamplePoint = rayOrigin;
	float stepSize = rayLength / (u_opticalDepthPointsNum - 1);
	float opticalDepth = 0;

	for (int i = 0; i < u_opticalDepthPointsNum; i++)
	{
		float localDensity = densityAtPoint(densitySamplePoint);
		opticalDepth += localDensity * stepSize;

		densitySamplePoint += rayDir * stepSize;
	}
	return opticalDepth;
}

vec3 getLight(vec3 rayOrigin, vec3 rayDir, float rayLength, vec3 originalColor)
{
	vec3 inScatterPoint = rayOrigin;
	float stepSize = rayLength / (u_scatteringPointsNum - 1);
	vec3 inScatterLight = vec3(0);
	float viewRayOpticalDepth;

	for (int i = 0; i < u_scatteringPointsNum; i++)
	{
		float sunRayLength = raySphere(inScatterPoint, -u_lightDir, u_planetPos, u_atmR);
		float sunRayOpticalDepth = opticalDepth(inScatterPoint, -u_lightDir, sunRayLength);
		viewRayOpticalDepth = opticalDepth(inScatterPoint, -rayDir, stepSize * i);

		vec3 transmittance = exp(-(sunRayOpticalDepth + viewRayOpticalDepth) * u_sactteringCoefficients);
		float localDensity = densityAtPoint(inScatterPoint);

		inScatterLight += transmittance * localDensity * stepSize * u_sactteringCoefficients;
		inScatterPoint += rayDir * stepSize;
	}

	float originalColorTransmittance = exp(-viewRayOpticalDepth);

	//return vec3(originalColorTransmittance);
	//return inScatterLight;
	return originalColor * originalColorTransmittance + inScatterLight;
}

void main()
{
   vec2 uv = pos.xy * 0.5 + 0.5;

   vec3 rayDir = normalize(originalPos - u_cameraPos);

   vec2 atmInter = sphIntersect(u_cameraPos, rayDir, u_planetPos, u_atmR);

   vec3 pa = u_cameraPos + rayDir * atmInter.x;
   vec3 pb = u_cameraPos + rayDir * atmInter.y;

   vec2 plInter = sphIntersect(u_cameraPos, rayDir, u_planetPos, u_planetR);

    if (plInter.x >= 0.0)
    {
    	pb = u_cameraPos + rayDir * max(plInter.x, 0.0);
    	//gl_FragColor = vec4(0.0, 1.0, 0.0, 0.5);
    	//return;
    }

   vec3 col = texture(mainTex, uv).rgb;

   //col = mix(col, vec3(1.0), length(pb - pa) / 2.0);

   col = getLight(pa, normalize(pb - pa), length(pb - pa), col);

   FragColor = vec4(col, 1.0);

   //FragColor = vec4(texture(diffuse0, pos.xy).rgb, 1.0);
}