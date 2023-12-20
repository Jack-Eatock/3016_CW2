#pragma once

//GLEW
#include <GL/glew.h>

//framebuffer_size_callback() needs GlFW, so include moved here
#include <GLFW/glfw3.h>

//STD
#include <iostream>

//Called on window resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

//Processes user input on a particular window
void ProcessUserInput(GLFWwindow* WindowIn);
