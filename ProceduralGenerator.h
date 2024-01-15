#ifndef PRECEDURALGENERATOR_CLASS_H
#define PRECEDURALGENERATOR_CLASS_H

#include<vector>
#include"Model.h"
#include"FastNoiseLite.h"

class ProceduralGenerator
{
public:
	// Starts the procedural generation at the desired position, size, with specific spacing between objects, a set seed and allows for the desired objects to be set.
	ProceduralGenerator(glm::vec3 position, int size, float spacing, float min, float seed, vector<string> files);
	void Draw(Shader& shader, CamController& camera, glm::vec4 lightColor, glm::vec3 SpotLightPositions[], LightSettings pointLights[]); // Iterates over all meshes generated and tells them to draw.
private:
	std::vector<Model> models; // Stores all generated meshes.
};

#endif