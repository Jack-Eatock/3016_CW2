#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include<string>

#include"VertexArrayObject.h"
#include"EntityBufferObject.h"
#include"CamController.h"
#include"Texture.h"

// Allows more information to be stored for the lights. 
static struct LightSettings
{
	LightSettings(glm::vec3 _pos, glm::vec4 _color, float _intensity)
	{
		position = _pos;
		color = _color;
		intensity = _intensity;
	}
	glm::vec3 position;
	glm::vec4 color;
	float intensity;
};


class Mesh {
public:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	VertexArrayObject VAO;
	Mesh() {};
	// Generates a mesh based on the Verts, Indices and textures that are passed in.
	Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures);

	// Draws the mesh to the screen in the provided shader.
	void Draw(Shader& shader, CamController& camera, glm::vec3 objectPos, glm::mat4 objectModel, glm::vec4 lightColor, glm::vec3 SpotLightPositions[], LightSettings pointLights[]);

	// Keeps track of the meshs properties.
	glm::vec3 position = glm::vec3(1.0f);
	float rotationX, rotationY, rotationZ, scale = 1.0f;
};

#endif
