#pragma once


#include <vector>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//Shape class used to draw basic shapes when given and passed the vertices of the shape.

class Shape {

public:
	//Constructor
	Shape(std::vector<glm::vec3> vertices);

	//Destructor free up memory
	~Shape() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}

	void draw();

	std::vector<glm::vec3> vertices;
	GLuint VBO = 0;
	GLuint VAO = 0;


private:
	void setUpMesh();

};