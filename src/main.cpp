//Open GL Libs
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

//Standard Lib
#include <iostream>
#include<vector>

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


static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
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

	float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f
	};


	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	std::vector<glm::vec3> vertice = { glm::vec3(0.25f, 0.25f, 0.0f), glm::vec3(0.5f, 0.25f, 0.0f), glm::vec3(0.30f, 0.0f, 0.0f) };
	Shape triangle = Shape(vertice);

	//shader loading example
	Shader s;
	s.loadShaderProgramFromFile(RESOURCES_PATH "vertex.vert", RESOURCES_PATH "fragment.frag");

	GLint translationLocation;



	while (!glfwWindowShouldClose(window))
	{
		int width = 0, height = 0;

		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);


		s.bind();

		float time = glfwGetTime();
		float scale = sin(time) + 0.1f;
		translationLocation = s.getUniform("ourTranslation");

		//Creates identity matrix
		glm::mat4 translation = glm::mat4(1.0f);
		//Scalar vector for multiplication
		glm::vec3 scalar = glm::vec3(scale * 2.0f, scale, 0.0f);

		translation = glm::scale(translation, scalar);

		glUniformMatrix4fv(translationLocation, 1, GL_TRUE, glm::value_ptr(translation));
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		triangle.draw();


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//there is no need to call the clear function for the libraries since the os will do that for us.
	//by calling this functions we are just wasting time.
	//glfwDestroyWindow(window);
	//glfwTerminate();
	return 0;
}
