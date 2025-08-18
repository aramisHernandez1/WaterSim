#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;


uniform mat4 MVP;
uniform float time;

vec3 newPos;

out vec3 normal;
out vec3 fragPos;

void main()
{
	//Sum of sines
	float wave1 = sin(aPos.x * 2.0 + time * 1.5);
	float wave2 = sin(aPos.z * 3.5 - time * 2.0);
	float wave3 = sin((aPos.x + aPos.z) * 1.0 + time * 1.0);

	//Combine sum of sines
	float displacement = (wave1 + wave2 + wave3) * 0.2;

	//Offset vertex position in the y-axis.
	newPos = aPos + vec3(0.0, displacement, 0.0);

	gl_Position = MVP * vec4(newPos, 1.0);

	//Note this normal is incorrect
	//THe normal is currently for the lighting of a flate surface.
	//Calculations need to be done for it to be the lighting of the waves
	normal = aNormal;

	//Note change the position to new position when fixed the normals.
	fragPos = vec3(vec4(aPos, 1.0));

}