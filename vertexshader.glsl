#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normal;
void main()
{
	vec4 mvp = proj * view * model * vec4(aPos, 1.0);
	gl_Position = vec4(mvp.xyzw);
	FragPos = vec3(model * vec4(aPos, 1.0));	
	TexCoord = aTexCoord;
	Normal = aNormal;
}