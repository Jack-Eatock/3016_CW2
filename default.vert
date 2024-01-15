#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec3 aColor;
// Normals (not necessarily normalized)
layout (location = 2) in vec3 aNormal;
// Texture Coordinates
layout (location = 3) in vec2 aTex;

// Outputs the current position for the Fragment Shader
out vec3 crntPos;
// Outputs the color for the Fragment Shader
out vec3 color;
// Outputs the normal for the Fragment Shader
out vec3 Normal;
// Outputs the texture coordinates to the Fragment Shader
out vec2 texCoord;

// Imports the camera matrix from the main function, required for calculations.
uniform mat4 camMatrix;
// Imports the model matrix from the main function, gives context to where the object is
uniform mat4 model;

void main()
{
	// calculates current position
	crntPos = vec3(model * vec4(aPos, 1.0f));
	// Outputs the positions/coordinates of all vertices
	gl_Position = camMatrix * vec4(crntPos, 1.0);
	// Assigns the colors from the Vertex Data to "color"
	color = aColor;
	// Assigns the texture coordinates from the Vertex Data to "texCoord"
	texCoord = aTex;
	// Assigns the normal from the Vertex Data to "Normal"
	Normal = aNormal;
}