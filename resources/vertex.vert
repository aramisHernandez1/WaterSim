#version 330 core

layout (location = 0) in vec3 p;
layout (location = 1) in float inFadeSpeed;

out float outFadeSpeed;

//uniform mat4 ourTranslation;

void main()
{
	gl_Position = vec4(p, 1);
	outFadeSpeed = inFadeSpeed;

}