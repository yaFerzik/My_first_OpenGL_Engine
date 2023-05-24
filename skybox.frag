#version 330 core
out vec4 FragColor;

in vec3 texCoords;

uniform samplerCube skybox;
uniform vec3 lightDir;

void main()
{   
    vec3 col = texture(skybox, texCoords).xyz;

    float r1 = 0.999;
    float r2 = 0.995;

    float b = max(0.0, dot(normalize(texCoords), -lightDir));
    float b1 = step(0.999, b);
    float b2 = pow(max(min((b - r2) / (r1 - r2), 1.0), 0.0), 5.0);

    col = mix(col, vec3(1.0, 1.0, 0.7), max(b1, b2));

    FragColor = vec4(col, 1.0);
}