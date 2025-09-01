#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};


class Camera {

public:
	Camera(glm::vec3 pos);

	void setCameraSpeed(float speed);
	glm::vec3 getPosition();

	void updateViewMatrix();
	glm::mat4 getViewMatrix();

	void processKeyboard(Camera_Movement direction, float dt);
	void processMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch = true);
	void processMouseScroll(float yOffset);

	float getZoom();

	Camera_Movement direction; 

private:
	float speed;

	float yaw;
	float pitch;
	float mouseSensitivity;
	float zoom;

	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	glm::mat4 view;


	void updateCameraVectors();
};