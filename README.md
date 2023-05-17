# scop - Basic GPU rendering with OpenGL
The goal of this project is to interpret a wavefront .obj file and display the object using modern OpenGL.

## NOTE
This project is still under development. It is being written on MacOS. Testing / compatibility for other systems has not yet been done.

## To Do
- Parse .bmp files without stb_image
- Create Proper classes for Wavefront Objects and Materials and parse the file into them
- Implement solutions when texture coords / normal vectors are not given
  -  textures: default mapping / different randomized color for each polygon
  -  normals: no light
- Clean up general structure
- Optional:
  - file browser
  - sliders
  - test linux compatibility
- Features section in README.md

## Setup
Clone the repository onto your system and run `make`. 
If everything compiled well, you should have the executable `scop` in your directory. Run this executable to start the program.

## How to use
Executing `scop` will open a window displaying the currently provided object file. To change this object file, look in main.cpp for the line:
```c++
std::string path("resources/skull2.obj");
```
and replace the string with the desired path.
You can rotate the object around all 3 of its axes using the arrow keys, 'R' and 'T'. 
You can zoom in and out with the keys 'I' and 'O'.
You can move the camera up down, left and right with the 'W' 'A' 'S' 'D' keys.

<img width="400" alt="skull" src="https://github.com/kmeixner247/scop/assets/81682578/a5a7dcbb-16ef-4d74-9ef5-5599d6057bba">
