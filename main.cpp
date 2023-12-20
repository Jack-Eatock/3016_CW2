#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int main()
{
	// Initialize GLFW
	glfwInit();

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

	// Sets up GLAD. Which we use to configure and manage OpenGL so that it can support any platform, GPU etc. 
	gladLoadGL();

	glViewport(0, 0, 800, 800);

	glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // Sets the background colour
	glClear(GL_COLOR_BUFFER_BIT); // Applies the change to the back buffer.

	// Swaps back buffer with front buffer (Applies the changes to colour we made)
	glfwSwapBuffers(window);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}


	// Close window and terminate program.
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}