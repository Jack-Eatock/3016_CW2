#include"Model.h"
#include"SkyBox.h"
#include "ProceduralGenerator.h"

const unsigned int width = 800, height = 800;

Vertex lightVertices[] =
{ //     COORDINATES     //
	Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
	Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
	Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
};

GLuint lightIndices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};


int main()
{
	// Initialize GLFW
	glfwInit();

	#pragma region Create Window

	// Lets GLFW know what version of OpenGL is being used. (We are using 3.3)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Lets GLFW know we want only the modern CORE functions.

	// Creates the window we use to display
	GLFWwindow* window = glfwCreateWindow(width, height, "SpaceGame", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); // Brings the window into the context of this program

	#pragma endregion

	gladLoadGL(); // Sets up GLAD. Which we use to configure and manage OpenGL so that it can support any platform, GPU etc. 
	glViewport(0, 0, width, height); // viewport of OpenGL in the Window

	Texture textures[]
	{
		Texture(string("planks.png"), "diffuse", 0),
		Texture(string("planks.png"), "specular", 1)
	};

	// positions of the point lights
	glm::vec3 SpotLightPositions[] = {
		glm::vec3(20.0f, 1.0f, .5f),
		glm::vec3(1.0f,  .3f, -.5f),
		glm::vec3(4.0f,  0.0f,22.0f),
		glm::vec3(1.0f, .3f, 1.0f)
	};

	// positions of the point lights
	glm::vec3 PointLightPositions[] = {
		glm::vec3(20.0f, 1.0f, .5f),
		glm::vec3(1.0f,  .3f, -.5f),
		glm::vec3(4.0f,  0.0f,22.0f),
		glm::vec3(1.0f, .3f, 1.0f)
	};

	Shader shaderProgram("default.vert", "default.frag"); // Setting up Shader
	

	// Shader for light cube
	Shader lightShader("light.vert", "light.frag");
	// Store mesh data in vectors for the mesh
	std::vector <Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector <GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));


	// Procedural Generation - Debris
	ProceduralGenerator pc(glm::vec3(100.0f, -60.0f, -70.0f), 34, 2.5f, .75f, rand() % (100), vector<string>{
			"Models/Debris1/SpaceshipDestroyed.obj",
			"Models/Debris2/SpaceshipDestroyed.obj",
			"Models/Debris3/SpaceshipDestroyed.obj"
	});

	// Procedural Generation 2 - Astroid Belt
	ProceduralGenerator pc2(glm::vec3(-100.0f, -100.0f, -90.0f), 30, 3.0f, .68f, rand() % (100), vector<string>{
			"Models/Rocks/Rock1/Rock1.obj",
			"Models/Rocks/Rock2/Rock1.obj",
			"Models/Rocks/Rock3/Rock1.obj",
			"Models/Rocks/Rock4/Rock1.obj"
	});

	// Procedural Generation 3 - Astroid and Debris
	ProceduralGenerator pc3(glm::vec3(6.0f, 2.0f, -160.0f), 26, 3.0f, .71f, rand() % (100), vector<string>{
			"Models/Rocks/Rock1/Rock1.obj",
			"Models/Rocks/Rock2/Rock1.obj",
			"Models/Debris2/SpaceshipDestroyed.obj",
			"Models/Rocks/Rock3/Rock1.obj",
			"Models/Rocks/Rock4/Rock1.obj"
	});


	//// Create light mesh
	std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
	Mesh light(lightVerts, lightInd, tex);
	Mesh light1(lightVerts, lightInd, tex);
	Mesh light2(lightVerts, lightInd, tex);
	Mesh light3(lightVerts, lightInd, tex);

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	//glm::vec3 lightPos = glm::vec3(1.0f, 2.0f, 1.0f);
	glm::mat4 testModel;

	// SkyBox
	Shader skyboxShader("Skybox.vert", "Skybox.frag");
	glUniform1i(glGetUniformLocation(skyboxShader.ID, "skybox"), 0);

	SkyBox skybox;

	lightShader.Activate();
	shaderProgram.Activate();

	Model ourModel3("Models/BackPack/backpack.obj", glm::vec3(50.0f, 1.0f, 3.0f), true);
	Model MainSpaceShipDestroyed("Models/MainDestroyedShip/SpaceshipDestroyed.gltf" ,glm::vec3(10.0f, -8.0f, -60.0f));
	
	Model DebrisCircle("Models/DebrisCircle/SpaceshipDestroyed.obj", glm::vec3(8.0f, -8.0f, -55.0f));
	DebrisCircle.rotationZ = 12.0f;
	MainSpaceShipDestroyed.rotationZ = 12.0f;
	MainSpaceShipDestroyed.rotationY = 45.0f;
	Model ourModel2("Models/New Folder(2)/Fighter_01.gltf" ,glm::vec3(-10.0f, 1.0f, 3.0f));
	Model debris("Models/Debris1/SpaceshipDestroyed.obj"  ,glm::vec3(-35.0f, 1.0f, 3.0f));

	glEnable(GL_DEPTH_TEST); // Closer objects rendered on top. 

	CamController camera(width, height, glm::vec3(8.0f,20.0f, 10.0f));

	float rotation = 0.0f;
	float slowerRotation = 0.0f;
	float verySlowRotation = 0.0f;
	double prevTime = glfwGetTime();

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // Bg colour
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear back buffer
		
		camera.Inputs(window);
		camera.UpdateMatrix(45.0f, .1f, 200.0f);


		double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1 / 60) {
			rotation += .050f;
			slowerRotation += .030;
			prevTime = crntTime;
		}

		//light.Draw(lightShader, camera, SpotLightPositions[0], glm::mat4(1.0f), lightColor, SpotLightPositions, PointLightPositions);
		//light1.Draw(lightShader, camera, SpotLightPositions[1], glm::mat4(1.0f), lightColor, SpotLightPositions, PointLightPositions);
		//light2.Draw(lightShader, camera, SpotLightPositions[2], glm::mat4(1.0f), lightColor, SpotLightPositions, PointLightPositions);
		//light3.Draw(lightShader, camera, SpotLightPositions[3], glm::mat4(1.0f), lightColor, SpotLightPositions, PointLightPositions);
		
		
		MainSpaceShipDestroyed.Draw(shaderProgram, camera, lightColor, SpotLightPositions, PointLightPositions);
		DebrisCircle.rotationY = slowerRotation;
		DebrisCircle.Draw(shaderProgram, camera, lightColor, SpotLightPositions, PointLightPositions);

		//ourModel2.Draw(shaderProgram, camera, lightColor, SpotLightPositions, PointLightPositions);
		//ourModel3.Draw(shaderProgram, camera, lightColor, SpotLightPositions, PointLightPositions);

		//debris.rotationY = rotation;
		//debris.Draw(shaderProgram, camera, lightColor, SpotLightPositions, PointLightPositions);

		pc.Draw(shaderProgram, camera, lightColor, SpotLightPositions, PointLightPositions);
		pc2.Draw(shaderProgram, camera, lightColor, SpotLightPositions, PointLightPositions);
		pc3.Draw(shaderProgram, camera, lightColor, SpotLightPositions, PointLightPositions);

		skybox.Draw(skyboxShader, camera, width, height);
	
		glfwSwapBuffers(window);// Swap the back buffer with the front buffer
		glfwPollEvents();
	}

	#pragma endregion

	shaderProgram.Delete();
	lightShader.Delete();
	skyboxShader.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
