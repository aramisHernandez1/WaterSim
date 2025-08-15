#version 330 core

layout (location = 0) in vec3 p;

out vec3 vertColor;

//uniform mat4 ourTranslation;
uniform mat4 MVP;

//uniform mat4 model;
//uniform mat4 view;
//uniform mat4 projection;



void main()
{
	gl_Position = MVP * vec4(p, 1.0);
	vertColor = p;

}