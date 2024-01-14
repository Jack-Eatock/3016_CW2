#include "ProceduralGenerator.h"
#include <cstdlib> 
#include <iostream> 
#include <time.h> 

ProceduralGenerator::ProceduralGenerator(glm::vec3 position, float size, float spacing, vector<string> files)
{
	//Assigning perlin noise type for map
	FastNoiseLite TerrainNoise;
	//Setting noise type to Perlin
	TerrainNoise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
	//Sets the noise scale
	TerrainNoise.SetFrequency(0.5f);
	//Generates a random seed between integers 0 & 100
	int terrainSeed = rand() % 100;
	//Sets seed for noise
	TerrainNoise.SetSeed(terrainSeed);
	float noise = 0.0f;

	int num = 0;
	for ( int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			for (int z = 0; z < size; z++)
			{
				noise = TerrainNoise.GetNoise(float(x), float(y), float(z));
				//std::cout << " noise " << noise << " " << x << " " << y << std::endl;
				if (noise > .75f || noise < -.75f)
				{
					num++;

					// Where to spawn?
					glm::vec3 newPos = glm::vec3(x, y, z);
					newPos *= spacing;
					newPos = position + newPos;

					// Which model to spawn?
					string modelFile = files[rand() % files.size()];
					Model newObject(modelFile, newPos, true);

					// Rotate model
					int axis = rand() % (3);
					int angle = rand() % 360;

					if (axis == 0) 
						newObject.rotationX = angle;
					else if (axis == 1)
						newObject.rotationY = angle;
					else
						newObject.rotationZ = angle;

					models.push_back(newObject);
				}
			}
		}
	}
	std::cout << "[Procedural Gen] - Number Generated: " << num << std::endl;
}

void ProceduralGenerator::Draw(Shader& shader, CamController& camera, glm::vec4 lightColor, glm::vec3 SpotLightPositions[], glm::vec3 pointLightPositions[])
{
	if (models.size() <= 0)
	{
		std::cout << "Procedural gen - No models? " << std::endl;
		return;
	}

	std::cout << models.size() << " " << models[0].position.x << " " << models[1].position.x << models[2].position.x << std::endl;
	for (int i = 0; i < models.size(); i++)
	{
		
		models[i].Draw(shader, camera, lightColor, SpotLightPositions, pointLightPositions);
	}

}
