#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

// Vertices coordinates
GLfloat vertices[] =
{
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
	-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
	0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
};

// Indices for vertices order
GLuint indices[] =
{
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Upper triangle
	5, 4, 1 // Lower right triangle
};

int main()
{
	// Initialize GLFW
	glfwInit();

	#pragma region Create Window

	// Lets GLFW know what version of OpenGL is being used. (We are using 3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Lets GLFW know we want only the modern CORE functions.

	// Creates the window we use to display
	GLFWwindow* window = glfwCreateWindow(800, 800, "SpaceGame", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); // Brings the window into the context of this program

	#pragma endregion

	gladLoadGL(); // Sets up GLAD. Which we use to configure and manage OpenGL so that it can support any platform, GPU etc. 
	glViewport(0, 0, 800, 800); // viewport of OpenGL in the Window

	Shader shaderProgram("default.vert", "default.frag"); // Setting up Shader

	VAO VAO1; // Set up vertex reference object
	VAO1.Bind(); // Bind the vertex object

	VBO VBO1(vertices, sizeof(vertices)); // Set up Vertex Buffer reference object
	EBO EBO1(indices, sizeof(indices)); // Generates Element Buffer Object and links it to indices

	VAO1.LinkVBO(VBO1, 0); 	// Links array object to buffer

	// Unbind all to prevent accidentally modifying them
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // Bg colour
		glClear(GL_COLOR_BUFFER_BIT); // Clear back buffer
		shaderProgram.Activate(); // Sets opengl Shader to use
		VAO1.Bind(); // Tells opengl which vertex array to use
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);	// Draw primitives, number of indices, datatype of indices, index of indices
		glfwSwapBuffers(window);// Swap the back buffer with the front buffer
		glfwPollEvents();
	}

	#pragma endregion

	VAO1.Delete(); VBO1.Delete(); EBO1.Delete();
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}