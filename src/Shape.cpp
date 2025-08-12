#include <Shape.hpp>

//Constructor sets up the mesh and vertices, awaiting for the draw method to be called.
Shape::Shape(std::vector<glm::vec3> vertices) {
	this->vertices = vertices;
	this->setUpMesh();
}


void Shape::draw() {
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertices.size()));
	glBindVertexArray(0);
}

void Shape::setUpMesh() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}