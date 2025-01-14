#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include"shaderClass.h"

class CamController
{
public:
	// Position, rotation 
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, -0.5f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 cameraMatrix = glm::mat4(1.0f);
	glm::mat4 view;
	glm::mat4 projection;

	// Prevents the camera from jumping around when first clicking left click
	bool firstClick = true;

	// Stores the width and height of the window
	int width;
	int height;

	// Adjust the speed of the camera and it's sensitivity when looking around
	float speed = 0.005f;
	float sensitivity = 100.0f;

	CamController(int width, int height, glm::vec3 position);

	// Updates and exports the camera matrix to the Vertex Shader
	void UpdateMatrix(float FOVdeg, float nearPlane, float farPlanes);

	void Matrix(Shader& shader, const char* uniform);

	void Inputs(GLFWwindow* window, float crTime);
};
#endif