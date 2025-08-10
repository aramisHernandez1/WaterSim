#version 330 core

layout (location = 0) in vec3 p;

vec3 pos;
uniform float scaleValue;

void main()
{
	pos = p * scaleValue;
	gl_Position = vec4(pos, 1);

}