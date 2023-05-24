#version 330 core
out vec4 FragColor;


in vec3 pos;
in vec3 norm;
in vec3 Color;
in vec2 UV;

uniform sampler2D diffuse0;

uniform vec3 lightDir;

void main()
{
   vec3 col = texture(diffuse0, UV).rgb;

   float diff = max(0.0, dot(lightDir, norm));
   float amb = 0.03;

   float brightness = diff * (1.0 - amb) + amb;

   col *= brightness;

   FragColor = vec4(col, 1.0);

   //FragColor = vec4(texture(diffuse0, pos.xy).rgb, 1.0);
}

