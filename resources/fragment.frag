#version 330 core

layout (location = 0) out vec4 color;

in vec3 normal;


uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

vec3 ambient;

void main()
{
	float ambientStrength = 0.1;
	ambient = ambientStrength * lightColor;
	
	vec3 result = ambient * objectColor;
	
	color = vec4(lightColor * objectColor, 1);
}