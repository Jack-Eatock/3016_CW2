#version 330 core
out vec4 FragColor;

in vec3 texCoords;

// Allows for each face of the texture to be checked at once, Instead of having 6 textures, one for each face or so.
uniform samplerCube skybox;

void main()
{    
    FragColor = texture(skybox, texCoords);
}
