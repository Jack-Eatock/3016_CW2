#include"Texture.h"

Texture::Texture(std::string image, std::string texType, GLuint slot)
{
	SetupTexture(image, texType, slot);
}

void Texture::SetupTexture(std::string image, std::string texType, GLuint slot)
{
	// Assigns the type of the texture ot the texture object
	type = texType;
	fileDir = image;

	std::cout << "Load " << image << std::endl;

	// The width and height is obtained from the image itself.
	int widthImg, heightImg, numColCh;
	stbi_set_flip_vertically_on_load(true); // STBI has inverse axis to OpenGl so flip the image.
	unsigned char* bytes = stbi_load(image.c_str(), &widthImg, &heightImg, &numColCh, 0);  // Convert the image into bytes
	if (bytes)
	{
		std::cout << "HERE" << numColCh << std::endl;

		GLenum format = GL_RGBA;
		if (numColCh == 1)
			format = GL_RED;
		else if (numColCh == 3)
			format = GL_RGB;
		else if (numColCh == 4)
			format = GL_RGBA;

		glGenTextures(1, &ID); // Gen a texture object
		//glActiveTexture(GL_TEXTURE0 + slot); // Activate the texture object
		unit = slot;
		glBindTexture(GL_TEXTURE_2D, ID);// Bind it so we can edit it 

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR); // Add  properties to the texture. Such as nearest Neighbour
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  // STL is XYZ // Set the wrapping types.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, format, GL_UNSIGNED_BYTE, bytes);// Apply the image bytes to the texture to display.
		glGenerateMipmap(GL_TEXTURE_2D); // Generate mipmaps from the texture. So it can be displayed at different  distances etc.

		// Deletes the image data as it is already in the OpenGL Texture object
		stbi_image_free(bytes);

		// Unbinds the OpenGL Texture object so that it can't accidentally be modified
		glBindTexture(GL_TEXTURE_2D, 0);

		std::cout << "Loaded Texture:" << fileDir << std::endl;
	}

	else
		std::cout << "Failed to load texture" << std::endl;
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	// Gets the location of the uniform
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	// Shader needs to be activated before changing the value of a uniform
	shader.Activate();
	// Sets the value of the uniform
	glUniform1i(texUni, unit);
}

void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}