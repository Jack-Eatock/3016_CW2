#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include "shaderClass.h"
#include "Mesh.h"
#include <assimp/scene.h>
#include "Texture.h"

using namespace std;

class Model
{
public:
    // Creates a mode. Loads the desired texture, attaches the texture and positions the model where desired. Flip is used as some models have inverted textures.
    Model(string image, glm::vec3 objectPos, bool flip = false)
    {
        flipTexture = flip;
        loadModel(image.c_str(), objectPos, scale, flip);
    }
    // Calls the draw on each of its meshes. To present the model to the screen.
    void Draw(Shader& shader, CamController& camera, glm::vec4 lightColor, glm::vec3 SpotLightPositions[], LightSettings pointLights[]);
    glm::vec3 position = glm::vec3(1.0f);
    float rotationX, rotationY, rotationZ, scale = 1.0f;
private:
    // model data
    vector<Mesh> meshes;
    vector<Texture> textures_loaded;
    string directory;
    int numTextures;
    glm::mat4 model;
    bool flipTexture = false;
    // Gets the model into a standardised data format. Iterates over its nodes and obtains any info needed to display it.
    void loadModel(string path, glm::vec3 objectPos, float objectScale, bool flip = false);
    void processNode(aiNode* node, const aiScene* scene); // Retrieves the required data from this node of the imported model.
    Mesh processMesh(aiMesh* mesh, const aiScene* scene); // Iterates over each node to get the required data and build the mesh.
    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName); // Creates textures for this model and sets them up to be references later.
};

#endif