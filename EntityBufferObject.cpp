#include"EntityBufferObject.h"


// Constructor that generates a Elements Buffer Object and links it to indices
EntityBufferObject::EntityBufferObject(std::vector<GLuint>& indices)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);
}

// Binds the EBO
void EntityBufferObject::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

// Unbinds the EBO
void EntityBufferObject::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Deletes the EBO
void EntityBufferObject::Delete()
{
	glDeleteBuffers(1, &ID);
}