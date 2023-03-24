#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec4 vertexColor; // specify a color output to the fragment shader
uniform mat4 rotX;
uniform mat4 rotY;
uniform mat4 rotZ;
void main()
{
	gl_Position = rotX * rotY * rotZ * vec4(aPos, 1.0);
	vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // set the output variable to a dark-red color
}