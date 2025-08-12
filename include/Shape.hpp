#pragma once


#include <vector>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Shape {

public:
	
	Shape(std::vector<glm::vec3>);

	std::vector<glm::vec3> vertices;
	GLuint VBO = 0;
	GLuint VAO = 0;



private:
	void setUpMesh();

};