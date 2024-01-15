# Adrift through the debris
An interactive 3D experience amongst the stars. Explore the aftermath of a large galatic battle as you marvle at the spectacular views. This project was developed from scratch for the Comp3016 module 70% Coursework.

## How to run the program:

 1. Firstly download the repository.
 2. Within the project, navigate to x64/Debug and run the executable "COMP3016_CW2.exe"
 3. The game should start and you will already be able to interact! 
 4. Now I recommend that you have a look at the controls section.

## Controls:
- Look around by holding left click and moving your mouse!
- WASD to move forward, left, right and back.
- Ctrl to lower yourself.
- Spacebar to elevate yourself.
- Shift to move faster. 

## Links:
- [Github Repository](https://github.com/Jack-Eatock/COMP3016_CW2)
- Walkthrough Youtube Video

## Tools:
- OpenGL - Is the backbone of this project, providing the tools to render objects to the screen.
- C++ - The programming language used to write this project.
- Blender - A 3D modeling software that was used to create the models in this project.
- Affinity Photo - A photo editing tool that was used to create / edit the textures for this project.
- x64 - This project is build for x64

## Architecture and Design:
#### All of the logic is broken down as much as possible into smaller more manageable chucks, clases. This allows for cleaner, more efficient and most importantly more maintainable code.  I shall go over some of the more important classes:
- **Main.cpp** - This is the main class of the application, the program starts here and everything else is created by it. First it handles setting up all the required libraries such as glfw, before creating a window. It then proceeds to initiate many other objects which we will discuss further later, such as the Procedural Generation, Lights or Shaders. After setting everything up, such as creating the other objects, setting positions etc the Main.cpp class creates a loop that runs forever until the application is closed. This is the game loop. Within this loop the the core functionality of the applicaiton is performed. Every assets that needs to be drawn is drawn here, any transformations are performed here, basically anything that needs to occur every frame is ran here. Finally Main.cpp cleans up by commanding all of the objects to delete themselves, before closing the application.
- **AudioManager.cpp** - This class focuses only on audio, nothing else. It will initiate any libraries or objects required and play music and sound effects.
-  **CamController.cpp** - This class has two main roles. It handles controlling the camera's data such as the cameras rotation, position etc but it also handles all inputs regarding the camera. It will listen out for keyboard or mouse inputs and move the camera accordingly. 
- **EntityBufferObject.cpp** - This object is used to create a buffer for the indices and bind it to an array. Essential for rendering any object.
- **VertexArrayObject.cpp** - Generates a vertexArray and provides usefull functions for interacting with it such as "LinkAtttrib" which allows to easily link attributes such as positions or colours.
-  **VertexBufferObject.cpp** - Generates a buffer and binds it to a vertex array so that data can be passed to the shader.
-   **Light.cpp** - Stores all of the data for a specific light, such as the type of light, the intensity or its colour. Also generates a mesh that can be used to visualise the lights.
-   **Skybox.cpp** - Creates a mesh for the skybox, generates a CubeMapping texture for it, bind the CubeMapping texture to the appropriate textures and then renders it in the distance, to provide a nice skybox.
- **Mesh.cpp** - This object holds all of the important data for displaying a mesh (Could be apart of a large model). When initated it will set up it's vertex arrays and buffers as required as well as establishing its vertices, indices and textures. Then when it is requested to draw, it draws its mesh in relation to the shader that has been requested, passing in the required information to the shader to provide a nice look rendered mesh.
- **Model.cpp** - Similar to the Mesh.cpp this class holds all of the important data for rendering a model, which at its core is multiple meshes. When a Model is instantiated it will use the file directory provided to load and convert any 3D object format into a data structure that is generic. Once the object has been loaded and broken down into the generic data structure it is then broken down again into its core parts such as vertices or indices and seperated into meshes. These meshes are then saved and make up the model as a whole. When the model is requested to draw, it iterates over all of its meshes that make it up and request that they draw.
- **Texture.cpp**- This class takes in a file directory, retrieves the image, no matter the format and converts it into a reusable texture. It also has functions to set the texture active or to pass the texture to the shader.

## Unique Selling Points:
#### There are many space experiences and games out there.  What makes "Adrift through the debris" unique is its interesting approach towards story telling. Nothing is directly told to the player, you must explore and analyse the environement to form your own story. Instead  of being bombarded with information you find your self relaxing and taking in the views. Often subconciously making links between areas to form conclulsions on what must have happened. 
- Multiple  models loaded with custom textures and shaders.
- Procedural content generation also aids in standing out against competition. The generation makes the experience feel fresh everytime it is launched, luring players into spending far too long taking in the sites. 
- Attractive visuals keeps players interested in exploring.
- Fly around using an equiped jetpack with WASD and look around using the mouse.
- Audio, there is Music as well as sound effects. 
- Dynamic lights move around the scene, creating beautiful visuals.

## Dependencies:
####  In order to achieve a lot of the functionality required for this project. Quite a few libraries were used:
- Assimp - An import library for 3D models.
- Glad - A great library that manages function pointers for OpenGL.
- GLFW - Used for context and window management.
- GLM - A mathematics library.
- Stb - Used for generating and loading texturing.
- IrrKlang - Allows the playback of audio files.

## Acknowledgements:
#### Tutorials:
- https://learnopengl.com/
- https://www.youtube.com/watch?v=45MIykWJ-C4&ab_channel=freeCodeCamp.org

### External Assets:
- Skybox textures - https://opengameart.org/content/space-skyboxes-0
- Music and SFX - https://pixabay.com/

## References:
- Creating a Skybox using CubeMapping  -https://research.ncl.ac.uk/game/mastersdegree/graphicsforgames/cubemapping/Tutorial%2013%20-%20Cube%20Mapping.pdf
- Creating an outline shader using the stencil buffer - http://www.geoffprewett.com/blog/software/opengl-outline/index.html