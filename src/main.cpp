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


	//Drawing our shapes

	//First triangle
	std::vector<Vertex> vertice = { {glm::vec3(-0.5f, 0.5f, 0.0f), 1.0f}, {glm::vec3(0.0f, -0.5f, 0.0f), 1.0f}, {glm::vec3(-0.5f, -0.5f, 0.0f), 1.0f }, {glm::vec3(0.0f, 0.5f, 0.0f), 1.0f}};
	std::vector<unsigned int> indices = { 0, 1, 2, 0, 1, 3};
	Shape triangle = Shape(vertice, indices);

	/*
	//Second triangle
	std::vector<Vertex> vertice2 = { {glm::vec3(-0.49f, 0.5f, 0.0f), 2.0f}, {glm::vec3(0.01f, -0.5f, 0.0f), 2.0f}, {glm::vec3(0.01f, 0.5f, 0.0f), 2.0f} };
	std::vector<unsigned int> indices2 = { 0, 1, 2 };
	Shape triangle2 = Shape(vertice2, indices2);

	//Third triangle
	std::vector<Vertex> vertice3 = { {glm::vec3(0.5f, 0.5f, 0.0f), 3.0f}, {glm::vec3(0.02f, -0.5f, 0.0f), 3.0f}, {glm::vec3(0.5f, -0.5f, 0.0f), 3.0f} };
	std::vector<unsigned int> indices3 = { 0, 1, 2 };
	Shape triangle3 = Shape(vertice3, indices3);
	*/

	//shader loading example
	Shader shader;
	shader.loadShaderProgramFromFile(RESOURCES_PATH "vertex.vert", RESOURCES_PATH "fragment.frag");
	//Uniform location for translation.
	GLint translationLocation;
	GLint timeLocation;


	GLint MVPlocation;
	GLint modelLoc;
	GLint viewLoc; 
	GLint projLoc;

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
		timeLocation = shader.getUniform("time");
		//translationLocation = s.getUniform("ourTranslation");
		glUniform1f(timeLocation, time);



		//Set up our model view and projection matrix
		//Note for now this is just straight tooken from learnOpenGL
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(45.0f), 640.0f / 480.0f, 0.1f, 100.0f); //Note Idk what the numbers really mean currently, figure this out next time.

		//Will pass the multiplication off all three on a uniform
		//Multiple on CPU so we dont have to use the bus which is slow I believe.
		glm::mat4 MVP = projection * view * model;

		MVPlocation = shader.getUniform("MVP");
		/*
		modelLoc = shader.getUniform("model");
		viewLoc = shader.getUniform("view");
		projLoc = shader.getUniform("projection");


		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		*/

		glUniformMatrix4fv(MVPlocation, 1, GL_FALSE, glm::value_ptr(MVP));


		/*
		//glm::mat4 translation = glm::mat4(1.0f);
		//Scalar vector for multiplication
		//glm::vec3 scalar = glm::vec3(scale * 2.0f, scale, 0.0f);

		//translation = glm::scale(translation, scalar);

		//glUniformMatrix4fv(translationLocation, 1, GL_TRUE, glm::value_ptr(translation));
		*/

		//Draw all three triangles
		triangle.draw();
		//triangle2.draw();
		//triangle3.draw();


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//there is no need to call the clear function for the libraries since the os will do that for us.
	//by calling this functions we are just wasting time.
	//glfwDestroyWindow(window);
	//glfwTerminate();
	return 0;
}
