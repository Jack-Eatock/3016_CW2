# Adrift through the debris
An interactive 3D experience amongst the stars. Explore the aftermath of a large galatic battle as you marvle at the spectacular views.

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

## Tools
- OpenGL - Is the backbone of this project, providing the tools to render objects to the screen.
- C++ - The programming language used to write this project.
- Blender - A 3D modeling software that was used to create the models in this project.
- Affinity Photo - A photo editing tool that was used to create / edit the textures for this project.

## Architecture and Design:
All of the logic is broken down as much as possible into smaller more manageable chucks, clases. This allows for cleaner, more efficient and most importantly more maintainable code. 

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