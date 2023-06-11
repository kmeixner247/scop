# scop - Basic GPU rendering with OpenGL
The goal of this project is to interpret a wavefront .obj file and display the object using modern OpenGL.

## NOTE
This project was written on macOS. Testing / compatibility for other systems has not yet been done.

## To Do
- Features section in README.md

## Setup
Clone the repository onto your system and run `make`. 
If everything compiled well, you should have the executable `scop` in your directory.

## How to use
Execute `scop` with the relative paths to a .obj file and a .bmp file as arguments:

```./scop resources/textured_teapot.obj resources/bluetexture.bmp```

### Key bindings
#### Camera movement
*W:* Move camera up (positive Y)
*A:* Move camera left (negative X)
*S:* Move camera down (negative Y)
*D:* Move camera right (positive X)
*I:* Move camera forward (negative Z)
*O:* Move camera backward (positive Z)

#### Object transform
*Left arrow:* Turn object counterclockwise around *its own* Y-Axis
*Right arrow:* Turn object clockwise around *its own* Y-Axis
*Up arrow:* Turn object clockwise around *its own* X-Axis
*Down arrow:* Turn object counterclockwise around *its own* X-Axis
*R:* Turn object counterclockwise around *its own* Z-Axis
*T:* Turn object clockwise around *its own* Z-Axis
*K:* Scale object bigger
*L:* Scale object smaller
*Tab:* Switch object texture between random colours for each polygon and the provided texture

#### Environment
*1:* Use simple shader (no lighting effects)
*2:* Use lighting shader (Phong Lighting Model effects)


<img width="400" alt="skull" src="https://github.com/kmeixner247/scop/assets/81682578/a5a7dcbb-16ef-4d74-9ef5-5599d6057bba">
