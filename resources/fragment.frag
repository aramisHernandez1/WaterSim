#version 330 core

layout (location = 0) out vec4 color;

in vec3 vertColor;

uniform float time;

void main()
{
	float alpha = abs(sin( (time)/5 )	);


	color = vec4(alpha, 1, 1-alpha, 1);


}