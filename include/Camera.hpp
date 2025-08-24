#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


//Note come back to this class later dont have time to actually make the class right now.

class Camera {

public:
	Camera(glm::vec3 pos);

	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;

	glm::mat4 view;


};