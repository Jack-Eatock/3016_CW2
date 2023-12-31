#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VertexBufferObject.h"

class VertexArrayObject
{
public:
	// ID reference for the Vertex Array Object
	GLuint ID;
	// Constructor that generates a VAO ID
	VertexArrayObject();

	// Links a VBO to the VAO using a certain layout
	void LinkAttrib(VertexBufferObject& VBO, GLuint layout,  GLuint  numComponents, GLenum type, GLsizeiptr stride, void* offset);
	// Binds the VAO
	void Bind();
	// Unbinds the VAO
	void Unbind();
	// Deletes the VAO
	void Delete();
};
#endif