#version 330 core

layout (location = 0) out vec4 color;

in vec3 fragPos;
in vec3 normal;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

uniform vec3 viewPos;

vec3 ambient;


void main()
{
	//Ambient lighting
	float ambientStrength = 0.1;
	ambient = ambientStrength * lightColor;
	
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPos - fragPos);

	//Dont want negative lightning so 0.0 is our min
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	float specularStrength = 0.1;

	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;

	//Final result of lighting
	vec3 result = (ambient + diffuse + specular) * objectColor;
	
	color = vec4(result, 1);
}