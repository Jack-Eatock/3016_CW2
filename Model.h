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
    Model(string image)
    {
        loadModel(image.c_str());
    }
    void Draw(Shader& shader, CamController& camera, glm::vec3 objectPos, glm::mat4 objectModel, glm::vec4 lightColor, glm::vec3 SpotLightPositions[], glm::vec3 pointLightPositions[]);
private:
    // model data
    vector<Mesh> meshes;
    vector<Texture> textures_loaded;
    string directory;
    int numTextures;

    void loadModel(string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    
    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};

#endif