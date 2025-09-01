#include <Camera.hpp>
//Note: most of this camera class is from the learnOpenGL book
//Can later change this class if I want a better camera system but this really is all I need
//Don't need a complex or crazy camera for this project.


//Default camera values
const float YAW = -90.0f;
const float PITCH = 15.0f;
const float SPEED = 3.5f;
const float SENSITIVITY = 10.0f;
const float ZOOM = 45.0f;


//Note need to add roations with mouse
Camera::Camera(glm::vec3 pos) {
	position = pos;
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	worldUp = up;
	yaw = YAW;
	pitch = PITCH;
	speed = SPEED;
	zoom = ZOOM;

	updateCameraVectors();
}

void Camera::processKeyboard(Camera_Movement direction, float dt) {
	float velocity = speed * dt;
	if (direction == FORWARD)
		position += front * velocity;
	if (direction == BACKWARD)
		position -= front * velocity;
	if (direction == LEFT)
		position -= right * velocity;
	if (direction == RIGHT)
		position += right * velocity;
}

void Camera::processMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch) {
	xOffset *= mouseSensitivity;
	yOffset *= mouseSensitivity;

	yaw += xOffset;
	pitch += yOffset;

	//When pitch of outbounds makes sure it doesn't flip our screen
	if (constrainPitch) {
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
	}

	updateCameraVectors();
}

void Camera::processMouseScroll(float yOffset) {
	zoom -= (float)yOffset;
	if (zoom < 1.0f)
		zoom = 1.0f;
	if (zoom > 45.0f)
		zoom = 45.0f;
}

//Calculates front vector from Camera's updated Euler Angles
void Camera::updateCameraVectors() {
	//Calc our newFront vector
	glm::vec3 newFront;
	newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	newFront.y = sin(glm::radians(pitch));
	newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(newFront);

	//Re clac front and right vectors
	right = glm::normalize(glm::cross(front, worldUp)); //We normalize this because length decreases getting closer to 0 when we look up making us look up slower and slower.
	up = glm::normalize(glm::cross(right, front));
}



void Camera::updateViewMatrix() {
	view = glm::lookAt(position, position + front, up);
}


//Setters----------
void Camera::setCameraSpeed(float speed) {
	Camera::speed = speed;
}


//Getters-----------
glm::vec3 Camera::getPosition() {
	return position;
}

glm::mat4 Camera::getViewMatrix() {
	return view;
}

float Camera::getZoom() {
	return zoom;
}