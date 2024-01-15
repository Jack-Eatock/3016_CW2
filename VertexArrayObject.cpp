#include"VertexArrayObject.h"

// Constructor that generates a VAO ID
VertexArrayObject::VertexArrayObject()
{
	glGenVertexArrays(1, &ID);
}

/// <summary>
/// Binds an attribute to the array. For example vertices, indices etc.
/// </summary>
void VertexArrayObject::LinkAttrib(VertexBufferObject& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	VBO.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

// Binds the VAO
void VertexArrayObject::Bind()
{
	glBindVertexArray(ID);
}

// Unbinds the VAO
void VertexArrayObject::Unbind()
{
	glBindVertexArray(0);
}

// Deletes the VAO
void VertexArrayObject::Delete()
{
	glDeleteVertexArrays(1, &ID);
}