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

#define USE_GPU_ENGINE 0
extern "C"
{
	__declspec(dllexport) unsigned long NvOptimusEnablement = USE_GPU_ENGINE;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = USE_GPU_ENGINE;
}


struct Wave {
	float amplitude;
	float frequency;
	float speed;
	glm::vec2 direction;
};


static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
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
	generatePlaneGrid(1000, 1000, 10.0f, vertices, indices);

	
	Shape plane = Shape(vertices, indices);


	//shader loading example
	Shader shader;
	shader.loadShaderProgramFromFile(RESOURCES_PATH "vertex.vert", RESOURCES_PATH "fragment.frag");



	std::vector<Wave> waves = {
	{0.3f,  2.0f, 1.5f, glm::vec2(1.0f, 0.0f)},   // X-axis
	{0.2f,  3.5f, 0.8f, glm::vec2(0.0f, 1.0f)},   // Z-axis
	{0.15f, 4.0f, 1.2f, glm::vec2(0.7f, 0.7f)},   // diagonal (45°)
	{0.1f,  1.5f, 2.5f, glm::vec2(-1.0f, 0.2f)},  // mostly negative X
	{0.25f, 5.0f, 1.0f, glm::vec2(0.3f, -0.9f)},  // tilted diagonal
	{0.18f, 6.5f, 0.6f, glm::vec2(-0.7f, -0.7f)}, // opposite diagonal
	{0.22f, 2.5f, 1.8f, glm::vec2(0.9f, 0.1f)},   // shallow angle
	{0.12f, 8.0f, 0.4f, glm::vec2(0.5f, -0.5f)},  // small amplitude ripple
	{0.28f, 3.0f, 2.2f, glm::vec2(-0.3f, 0.95f)}, // steep tilt
	{0.2f,  7.0f, 1.3f, glm::vec2(0.2f, 0.8f)}    // almost Z
	};

	glm::vec3 cameraPos = glm::vec3(0.0f, 1.0f, 10.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	//glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	//glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget); //Direction is pointing in reverse of what we are targeting

	//Right axis
	//glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	//glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));

	//glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

	glm::mat4 view;
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);


	while (!glfwWindowShouldClose(window))
	{
		int width = 0, height = 0;

		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		//Bind out shader
		shader.bind();

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

		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(45.0f), 640.0f / 480.0f, 0.1f, 100.0f); //Note Idk what the numbers really mean currently, figure this out next time.

		//Will pass the multiplication off all three on a uniform
		//Multiple on CPU so we dont have to use the bus which is slow I believe.
		glm::mat4 MVP = projection * view * model;
		shader.setUniformMatrix4("MVP", MVP, GL_FALSE);

		glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
		shader.setUniformVec3("lightColor", lightColor);

		glm::vec3 lightPos = glm::vec3(10.0f, 5.0f, 0.0f);
		shader.setUniformVec3("lightPos", lightPos);

		glm::vec3 objectColor = glm::vec3(0.1f, 0.10f, 0.7f);
		shader.setUniformVec3("objectColor", objectColor);

		shader.setUniformInt("waveCount", (int)waves.size());


		for (int i = 0; i < waves.size(); i++) {
			std::string idx = "waves[" + std::to_string(i) + "]";

			shader.setUniformFloat((idx + ".amplitude").c_str(), waves[i].amplitude);
			shader.setUniformFloat((idx + ".frequency").c_str(), waves[i].frequency);
			shader.setUniformFloat((idx + ".speed").c_str(), waves[i].speed);
			shader.setUniformVec2((idx + ".direction").c_str(), waves[i].direction);
		}



		//Draw all our plane/waves
		plane.draw();


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//there is no need to call the clear function for the libraries since the os will do that for us.
	//by calling this functions we are just wasting time.
	//glfwDestroyWindow(window);
	//glfwTerminate();
	return 0;
}
