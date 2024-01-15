#include"CamController.h"
#include"AudioManager.h"

// Creates the camera object and assigns its basic values.
CamController::CamController(int width, int height, glm::vec3 position)
{
	CamController::width = width;
	CamController::height = height;
	Position = position;
}

// Performs the calculations required for view and projection.
void CamController::UpdateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	view = glm::mat4(1.0f); // Initializes  matrices for View and Proj
	projection = glm::mat4(1.0f);

	view = glm::lookAt(Position, Position + Orientation, Up); // Sets  the initial camera pos and rotation
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane); // Adds perspective to the scene

	cameraMatrix = projection * view;
}

void CamController::Matrix(Shader& shader, const char* uniform) 
{
	// Exports the camera matrix to the Vertex Shader
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

void CamController::Inputs(GLFWwindow* window, float crTime)
{
	// If any movement key is pressed play the movement sound.
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS ||
		glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS ||
		glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS ||
		glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS ||
		glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS ||
		glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) 
	{
		AudioManager::PlaySFX("AudioFiles/good-jetpack-sound-loop-96693.mp3");
	}
	else {
		AudioManager::StopSFX();
	}

	// Handles key inputs, applying movement in their direction.
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Position += speed * Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position += speed * -glm::normalize(glm::cross(Orientation, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position += speed * -Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position += speed * glm::normalize(glm::cross(Orientation, Up));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		Position += speed * Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		Position += speed * -Up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		// If shift is pressed increase the speed
		speed = 0.06f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		// If shift is released reduce the speed
		speed = 0.03f;
	}


	// Mouse inputs
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN); // Hides mouse cursor

		// Prevents camera from jumping on the first click
		if (firstClick)
		{
			glfwSetCursorPos(window, (width / 2), (height / 2));
			firstClick = false;
		}

		// Keeping track of the cursor position
		double mouseX;
		double mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		// Calculate the movement from the centre of the screen. Uses it to calculate the rotation to apply from sensitivity.
		float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
		float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;
		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

		// Locks the rotations
		if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
			Orientation = newOrientation;

		// Rotates horizontally
		Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

		// Sets mouse to centre of screen.
		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		// Unhides cursor since camera is not looking around anymore
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// Makes sure the next time the camera looks around it doesn't jump
		firstClick = true;
	}
}