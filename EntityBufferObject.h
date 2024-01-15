#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>
#include<vector>

class EntityBufferObject
{
public:
	// ID for this buffer object
	GLuint ID;
	// Constructs the entityBuffer with the provided indices.
	EntityBufferObject(std::vector<GLuint>& indices);

	// Binds the EBO
	void Bind();
	// Unbinds the EBO
	void Unbind();
	// Deletes the EBO
	void Delete();
};

#endif