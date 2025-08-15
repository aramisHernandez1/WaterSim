#version 330 core

layout (location = 0) in vec3 p;


uniform mat4 MVP;
uniform float time;

vec3 newPos;

void main()
{
	//Sum of sines
	float wave1 = sin(p.x * 2.0 + time * 1.5);
	float wave2 = sin(p.z * 3.5 - time * 2.0);
	float wave3 = sin((p.x + p.z) * 1.0 + time * 1.0);

	//Combine sum of sines
	float displacement = (wave1 + wave2) * 0.2;

	//Offset vertex position in the y-axis.
	newPos = p + vec3(0.0, displacement, 0.0);

	gl_Position = MVP * vec4(newPos, 1.0);

}