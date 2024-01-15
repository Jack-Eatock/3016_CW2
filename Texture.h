#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<glad/glad.h>
#include<stb/stb_image.h>
#include"shaderClass.h"

class Texture
{
public:
	GLuint ID; // The id of this texture
	std::string type;
	std::string fileDir;
	GLuint unit;  // The location of this texture from the shaders perspective.

	Texture() {};

	// Creates a texture from the specified file location. Also takes in the texture type such as diffuse of specular. And allows for a id to be given.
	Texture(std::string image, std::string texType, GLuint slot, bool flip = false);

	// Creates a texture from the specified file location. Also takes in the texture type such as diffuse of specular. And allows for a id to be given.
	void SetupTexture(std::string image, std::string texType, GLuint slot, bool flip = false);

	// Assigns a texture unit to a texture
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	// Binds a texture
	void Bind();
	// Unbinds a texture
	void Unbind();
	// Deletes a texture
	void Delete();
};
#endif
