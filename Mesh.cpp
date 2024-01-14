#include"Mesh.h"


Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures) 
{
	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::textures = textures;

	std::cout << "NEW MESH " << vertices.size() << " " << indices.size() << " " << textures.size() << std::endl;
	VAO.Bind(); // Bind the vertex object

	VertexBufferObject VBO(vertices); // Set up Vertex Buffer reference object
	EntityBufferObject EBO(indices); // Generates Element Buffer Object and links it to indices


	//// Links VBO attributes such as coordinates and colors to VAO
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, color));
	VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	VAO.LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)offsetof(Vertex, texUV));

	// Unbind all to prevent accidentally modifying them
	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();
}

void Mesh::Draw(Shader& shader, CamController& camera, glm::vec3 objectPos, glm::mat4 objectModel, glm::vec4 lightColor, glm::vec3 SpotLightPositions[], glm::vec3 pointLightPositions[])
{
	position = objectPos;

	shader.Activate();
	VAO.Bind();

	unsigned int numDiffuse = 0;
	unsigned int numSpecular = 0;
	
	// Textures
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		std::string num;
		std::string type = textures[i].type;

		if (type == "diffuse")
		{
			num = std::to_string(numDiffuse++);
		}
		else if (type == "specular") 
		{
			num = std::to_string(numSpecular);
		}
		
		//std::cout << "HERE " << (type + num).c_str() << std::endl;

		textures[i].texUnit(shader, (type + num).c_str(), i);
		textures[i].Bind();
	}

	// Transforms
	objectModel = glm::translate(objectModel, position); //position = 0,0,0
	objectModel = glm::rotate(objectModel, glm::radians(rotationX), glm::vec3(1, 0, 0));//rotation x = 0.0 degrees
	objectModel = glm::rotate(objectModel, glm::radians(rotationY), glm::vec3(0, 1, 0));//rotation y = 0.0 degrees
	objectModel = glm::rotate(objectModel, glm::radians(rotationZ), glm::vec3(0, 0, 1));//rotation z = 0.0 degrees
	objectModel = glm::scale(objectModel, glm::vec3(scale,scale,scale));//scale = 1,1,1

	// Spot Lights
  	for (int i = 0; i <4; i++)
	{
		std::string lightId = "spotLights[" + std::to_string(i) + "]";
		//std::cout << (lightId + ".position") << i << " " << SpotLightPositions[i].x << std::endl;
		glUniform3f(glGetUniformLocation(shader.ID, (lightId + ".position").c_str()), SpotLightPositions[i].x, SpotLightPositions[i].y, SpotLightPositions[i].z);
		glUniform3f(glGetUniformLocation(shader.ID, (lightId + ".direction").c_str()), 0.0f, -1.0f, 0.0f);

		glUniform1f(glGetUniformLocation(shader.ID, (lightId + ".cutOff").c_str()), .60f);
		glUniform1f(glGetUniformLocation(shader.ID, (lightId + ".outerCutOff").c_str()), .95f);

		glUniform1f(glGetUniformLocation(shader.ID, (lightId + ".constant").c_str()), 1.0f);
		glUniform1f(glGetUniformLocation(shader.ID, (lightId + ".linear").c_str()), 0.09f);
		glUniform1f(glGetUniformLocation(shader.ID, (lightId + ".quadratic").c_str()), 0.032f);

		glUniform3f(glGetUniformLocation(shader.ID, (lightId + ".ambient").c_str()), 0.01f, 0.01f, 0.01f);
		glUniform3f(glGetUniformLocation(shader.ID, (lightId + ".diffuse").c_str()), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(shader.ID, (lightId + ".specular").c_str()), .7f, .7f, .7f);
	}

    // Point Lights
	for (int i = 0; i < 4; i++)
	{
		std::string lightId = "pointLights[" + std::to_string(i) + "]";
		//std::cout << (lightId + ".position") << i << " " << SpotLightPositions[i].x << std::endl;
		glUniform3f(glGetUniformLocation(shader.ID, (lightId + ".position").c_str()), pointLightPositions[i].x, pointLightPositions[i].y, pointLightPositions[i].z);

		glUniform1f(glGetUniformLocation(shader.ID, (lightId + ".constant").c_str()), 1.0f);
		glUniform1f(glGetUniformLocation(shader.ID, (lightId + ".linear").c_str()), 0.09f);
		glUniform1f(glGetUniformLocation(shader.ID, (lightId + ".quadratic").c_str()), 0.032f);

		glUniform3f(glGetUniformLocation(shader.ID, (lightId + ".ambient").c_str()), 0.01f, 0.01f, 0.01f);
		glUniform3f(glGetUniformLocation(shader.ID, (lightId + ".diffuse").c_str()), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(shader.ID, (lightId + ".specular").c_str()), .7f, .7f, .7f);
	}

	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
	glUniform4f(glGetUniformLocation(shader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	camera.Matrix(shader, "camMatrix");
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}