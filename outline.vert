#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 camMatrix;
uniform mat4 model;

uniform float outlining;

void main()
{
	// Draws the sketch version larger but behind the original model. 
	// Makes it appear as if it has an outline. 
	// This needs more work, as currently it does not have much context for scale, rotation or position causing weird bugs.
	vec3 crntPos = vec3(model * outlining * vec4(aPos, 1.0f));
	gl_Position = camMatrix * vec4(crntPos, 1.0);

}
