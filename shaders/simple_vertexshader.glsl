#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec3 randomColor;

uniform mat4 modelMtx;
uniform mat4 viewMtx;
uniform mat4 projMtx;

out vec2 TexCoord;
out vec3 FragPos;
out vec4 aRandomColor;

void main()
{
	vec4 mvp = projMtx * viewMtx * modelMtx * vec4(aPos, 1.0);
	gl_Position = vec4(mvp.xyzw);
	FragPos = vec3(modelMtx * vec4(aPos, 1.0));	
	TexCoord = aTexCoord;
	aRandomColor = vec4(randomColor, 1.0);
}