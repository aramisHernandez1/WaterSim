#include <Shape.hpp>

//Constructor sets up the mesh and vertices, awaiting for the draw method to be called.
Shape::Shape(std::vector<Vertex> vertices, std::vector<unsigned int> indices) {
	this->vertices = vertices;
	this->indices = indices;
	this->setUpMesh();
}


//Draw method that should be used after contructor use, to make the object appear on the screen.
void Shape::draw() {
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

//Set Up our Buffers to draw the object.
//Also set up our extra attributes and pointers
void Shape::setUpMesh() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	//Position pointer for the xyz coords
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);

	//Pointer for the extra fade attribute.
	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::fadeSpeed));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}