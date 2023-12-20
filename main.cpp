#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";


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

	#pragma region Setup Shaders

	// Create Vertex Shader Object and get its reference
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);// Attach Fragment Shader source to the Fragment Shader Object
	glCompileShader(vertexShader); // Compile so gpu can read it.

	// Create Fragment Shader Object and get its reference
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL); // Attach Fragment Shader source to the Fragment Shader Object
	glCompileShader(fragmentShader); // Compile so gpu can read it.

	// Wrap into shader programes
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	#pragma endregion

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


	// Passing to the GPU
	// Reference objects for vertex array and buffer objects.
	GLuint VAO, VBO, EBO;

	// Generate the VAO and VBO (Array and buffer)
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO); // Make the VAO the current object. This lets us tweak it.
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // Bind the Buffer so that we can edit it.
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);// Setup buffer for the vertices

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
	glEnableVertexAttribArray(0);// Enable the Vertex Attribute so that OpenGL knows to use it

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Clear current object so we dont mess with it.
	glBindVertexArray(0); // Clear current object so we dont mess with it.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	#pragma region Game Loop


	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // Sets the background colour
		glClear(GL_COLOR_BUFFER_BIT); // Applies the change to the back buffer.
		glUseProgram(shaderProgram); // Tell OpenGL which Shader Program we want to use
		glBindVertexArray(VAO); // Tells OpenGL which vertex array to use.
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT,0);
		glfwSwapBuffers(window); // Swaps back buffer with front buffer (Applies the changes to colour we made)

		glfwPollEvents();
	}

	#pragma endregion

	// Delete objects to clean up
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	glDeleteBuffers(1, &EBO);

	// Close window and terminate program.
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}