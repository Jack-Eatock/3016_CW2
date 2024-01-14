#ifndef PRECEDURALGENERATOR_CLASS_H
#define PRECEDURALGENERATOR_CLASS_H

#include<vector>
#include"Model.h"
#include"FastNoiseLite.h"

class ProceduralGenerator
{
public:
	ProceduralGenerator(glm::vec3 position, float size, float spacing, vector<string> files);
	void Draw(Shader& shader, CamController& camera, glm::vec4 lightColor, glm::vec3 SpotLightPositions[], glm::vec3 pointLightPositions[]);
private:
	std::vector<Model> models;

};

#endif