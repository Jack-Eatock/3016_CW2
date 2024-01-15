#ifndef SKYBOX_CLASS_H
#define SKYBOX_CLASS_H

#include <string>
#include <vector>
#include"VertexArrayObject.h"
#include"EntityBufferObject.h"
#include"CamController.h"
#include"Texture.h"

class SkyBox
{
public:
	SkyBox();
	void Draw(Shader shader, CamController  camera, float width, float height);

private:
	unsigned int cubeTexture; // The reference to the texture that is applied to the skybox
	unsigned int skyboxVAO, skyboxVBO, skyboxEBO; 
};

#endif