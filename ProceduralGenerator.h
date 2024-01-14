#ifndef PRECEDURALGENERATOR_CLASS_H
#define PRECEDURALGENERATOR_CLASS_H

#include<vector>
#include"Model.h"
#include"FastNoiseLite.h"

class ProceduralGenerator
{
public:
	ProceduralGenerator(glm::vec3 position, int size, float spacing, float min, float seed, vector<string> files);
	void Draw(Shader& shader, CamController& camera, glm::vec4 lightColor, glm::vec3 SpotLightPositions[], LightSettings pointLights[]);
private:
	std::vector<Model> models;

};

#endif