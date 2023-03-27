#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	vec4 test = proj * view * model * vec4(aPos, 1.0);
	gl_Position = vec4(test.xyzw);
}