#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Camera {

public:
	Camera(glm::vec3 pos);

	void setCameraSpeed(float speed);
	glm::vec3 getPosition();

	void updateViewMatrix();
	glm::mat4 getViewMatrix();

	void moveUp(float dt);
	void moveDown(float dt);
	void moveLeft(float dt);
	void moveRight(float dt);
	void moveFoward(float dt);
	void moveBackward(float dt);

private:
	float speed;

	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;

	glm::mat4 view;
};