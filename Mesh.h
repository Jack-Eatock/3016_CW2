#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include<string>

#include"VertexArrayObject.h"
#include"EntityBufferObject.h"
#include"CamController.h"
#include"Texture.h"


class Mesh {
public:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	VertexArrayObject VAO;
	Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures);

	void Draw(Shader& shader, CamController& camera);
};

#endif
