#version 330 core

layout (location = 0) out vec4 color;

in float outFadeSpeed;
in vec3 vertColor;

uniform float time;

void main()
{
	float alpha = abs(sin( (time * outFadeSpeed)/5 )	);


	color = vec4(alpha, 1, 1-alpha, 1);


}