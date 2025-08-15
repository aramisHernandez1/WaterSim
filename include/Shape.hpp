#pragma once

//Standard libs
#include <vector>

//OpenGL libs
#include <glad/glad.h>

//Glm libs for math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>



//Shape class used to draw basic shapes when given and passed the vertices of the shape.
//Added the extra feature of having a fade speed to create fading triangles.


//Vertex struct with a extra attribute of the fadespeed of the vertex.
struct Vertex {
	glm::vec3 position;
};

class Shape {

public:
	//Constructor
	Shape(std::vector<Vertex> vertices, std::vector<unsigned int> indices);

	//Destructor free up memory
	~Shape() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}

	void draw();
	
	//Mesh Information
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	//Buffers/Array objects.
	GLuint VBO = 0;
	GLuint VAO = 0;
	GLuint EBO = 0;


private:
	void setUpMesh();

};