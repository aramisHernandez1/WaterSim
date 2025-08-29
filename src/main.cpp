//Open GL Libs
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

//Standard Lib
#include <iostream>
#include<vector>
#include <string>

//Glm Libs
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


//My headers
#include <Shape.hpp>
#include <openglDebug.h>
#include <demoShaderLoader.h>
#include <Camera.hpp>

#define USE_GPU_ENGINE 0
extern "C"
{
	__declspec(dllexport) unsigned long NvOptimusEnablement = USE_GPU_ENGINE;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = USE_GPU_ENGINE;
}


static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void processed_input(GLFWwindow* window, Camera *camera, float dt) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->moveFoward(dt);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->moveBackward(dt);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->moveRight(dt);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->moveLeft(dt);

}

//Helper method that generates a plane with a whole bunch of vertices, so we can displace the vertices to give us waves and other cool effects.
static void generatePlaneGrid(int cols, int rows, float size, std::vector<Vertex> &outVerts, std::vector<unsigned int> &outIndices) {
	outVerts.clear();
	outIndices.clear();


	const int vCountX = cols + 1;
	const int vCountZ = rows + 1;

	const float half = size * 0.5f;

	const float disX = size / cols;
	const float disZ = size / rows;

	outVerts.reserve(vCountX * vCountZ);

	for (int z = 0; z < vCountZ; ++z) {
		for (int x = 0; x < vCountX; ++x) {
			
			float posX = -half + (x * disX);
			float posZ = -half + (z * disZ);


			Vertex vertice;
			vertice.position = glm::vec3(posX, 0.0f, posZ);
			vertice.normal = glm::vec3(0.0f, 1.0f, 0.0f);
			outVerts.push_back(vertice);
		}
	}

	//add a constant 6 since we need 2 triangles
	//each traingle has 3 indices so 3 * 2 = 6.
	outIndices.reserve(cols * rows * 6);
	for (int z = 0; z < rows; ++z) {
		for (int x = 0; x < cols; ++x) {
			int i0 = z * vCountX + x;
			int i1 = z * vCountX + (x + 1);
			int i2 = (z + 1) * vCountX + x;
			int i3 = (z + 1) * vCountX + (x + 1);

			//Triangle 1 contains indices [0, 2, 1]
			outIndices.push_back(i0);
			outIndices.push_back(i2);
			outIndices.push_back(i1);

			//Trianlge 2 contains indices [1, 2, 3]
			outIndices.push_back(i1);
			outIndices.push_back(i2);
			outIndices.push_back(i3);
		}
	}

}




int main(void)
{

	if (!glfwInit())
		return -1;


#pragma region report opengl errors to std
	//enable opengl debugging output.
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#pragma endregion


	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //you might want to do this when testing the game for shipping


	GLFWwindow *window = window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwSetKeyCallback(window, key_callback);
	glfwMakeContextCurrent(window);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);



#pragma region report opengl errors to std
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(glDebugOutput, 0);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
#pragma endregion



	//Setting up our plane with its vertices
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	generatePlaneGrid(1000, 1000, 400.0f, vertices, indices);

	
	Shape plane = Shape(vertices, indices);


	//shader loading example
	Shader shader;
	shader.loadShaderProgramFromFile(RESOURCES_PATH "vertex.vert", RESOURCES_PATH "fragment.frag");


	Camera camera = Camera(glm::vec3(0.0f, 1.0f, 10.0f));
	glm::vec3 cameraPos = camera.getPosition();
	//glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	//glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	//glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	//glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget); //Direction is pointing in reverse of what we are targeting

	//Right axis
	//glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	//glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));

	//glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

	//glm::mat4 view;
	//view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	camera.updateViewMatrix();
	
	int waveCount = 350;

	float currentFrame = 0.0;
	float deltaTime = 0.0;
	float lastFrame = 0.0;

	while (!glfwWindowShouldClose(window))
	{
		int width = 0, height = 0;

		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		//Bind out shader
		shader.bind();

		//Delta time for physics (camera movement)
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//Set time for the fade effect.
		float time = glfwGetTime();
		shader.setUniformFloat("time", time);

		shader.setUniformVec3("viewPos", cameraPos);



		//Set up our model view and projection matrix
		//Note for now this is just straight tooken from learnOpenGL
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(-5.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(25.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		//glm::mat4 view = glm::mat4(1.0f);
		//view = glm::translate(view, glm::vec3(0.0f, -1.0f, -20.0f));
		
		camera.updateViewMatrix();

		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(45.0f), 640.0f / 480.0f, 0.1f, 100.0f); //Note Idk what the numbers really mean currently, figure this out next time.

		
		glm::mat4 view = camera.getViewMatrix();
		glm::mat4 MVP = projection * view * model;
		shader.setUniformMatrix4("MVP", MVP, GL_FALSE);

		glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
		shader.setUniformVec3("lightColor", lightColor);

		glm::vec3 lightPos = glm::vec3(1.5f, 5.0f, 1.0f);
		shader.setUniformVec3("lightPos", lightPos);

		glm::vec3 objectColor = glm::vec3(0.0f, 0.30f, 0.85f);
		shader.setUniformVec3("objectColor", objectColor);

		shader.setUniformInt("waveCount", waveCount);



		//Draw all our plane/waves
		plane.draw();

		processed_input(window, &camera, deltaTime);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//there is no need to call the clear function for the libraries since the os will do that for us.
	//by calling this functions we are just wasting time.
	//glfwDestroyWindow(window);
	//glfwTerminate();
	return 0;
}
