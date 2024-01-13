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
	void Draw(Shader shader, CamController  camera);

private:
	unsigned int cubeTexture;
	unsigned int skyboxVAO, skyboxVBO;
};

#endif