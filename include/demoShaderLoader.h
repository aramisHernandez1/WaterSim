#pragma once
#include <glad/glad.h>

//Glm headers
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Shader
{
	GLuint id = 0;

	bool loadShaderProgramFromData(const char *vertexShaderData, const char *fragmentShaderData);
	bool loadShaderProgramFromData(const char *vertexShaderData,
		const char *geometryShaderData, const char *fragmentShaderData);

	bool loadShaderProgramFromFile(const char *vertexShader, const char *fragmentShader);
	bool loadShaderProgramFromFile(const char *vertexShader,
		const char *geometryShader, const char *fragmentShader);

	void bind();

	void clear();

	GLint getUniform(const char *name);

	//Uniform setter methods
	void setUniformInt(const char* name, const int value);
	void setUniformFloat(const char* name, const float value);
	void setUniformVec2(const char* name, glm::vec2 value);
	void setUniformVec3(const char* name, glm::vec3 value);
	void setUniformMatrix4(const char* name, glm::mat4 value, GLboolean readMode);
};

GLint getUniform(GLuint shaderId, const char *name);


