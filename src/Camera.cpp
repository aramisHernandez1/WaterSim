#include <Camera.hpp>

//Note need to add roations with mouse
Camera::Camera(glm::vec3 pos) {
	position = pos;
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);

	speed = 0.05f;
}


void Camera::setCameraSpeed(float speed) {
	Camera::speed = speed;
}

void Camera::updateViewMatrix() {
	view = glm::lookAt(position, position + front, up);
}

glm::vec3 Camera::getPosition() {
	return position;
}

glm::mat4 Camera::getViewMatrix() {
	return view;
}


//Directional functions for walking camera
void Camera::moveUp(float dt) {
	
}

void Camera::moveDown(float dt) {
	
}

void Camera::moveLeft(float dt) {
	position += glm::normalize(glm::cross(front, up) * (speed * dt));
}

void Camera::moveRight(float dt) {
	position -= glm::normalize(glm::cross(front, up) * (speed * dt));
}

void Camera::moveFoward(float dt) {
	position += (front * (speed * dt));
}

void Camera::moveBackward(float dt) {
	position -= (front * (speed * dt));
}