#version 330 core

layout (location = 0) in vec3 p;

uniform mat4 ourTranslation;

void main()
{
	gl_Position = ourTranslation * vec4(p, 1);

}